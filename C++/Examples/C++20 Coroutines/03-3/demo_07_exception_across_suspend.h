#pragma region MINE
#pragma once

#include "demo_common.h"
#include "types/manual_resume_awaitable.h"
#include "types/native_task.h"
#include "types/native_throw_generator.h"
#include "types/simple_task.h"
#include <coroutine>
#include <stdexcept>

inline void simple_generator_throw_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_generator_frame*>(base);

	switch (frame->state_index) {
	case 0:
		trace_frame_case(trace_mode::simple, 0);
		trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_always");
		trace_log(trace_mode::simple, "[Promise:yield_value]", "1");
		frame->promise.current_value = 1;
		frame->state_index = 1;
		return;

	case 1:
		trace_frame_case(trace_mode::simple, 1);
		trace_log(trace_mode::simple, "[Frame:throw]", "throw after co_yield");
		frame->promise.unhandled_exception();
		frame->promise.done = true;
		frame->state_index = 2;
		return;

	case 2:
		trace_frame_case(trace_mode::simple, 2);
		frame->at_final_suspend = true;
		frame->state_index = 3;
		return;

	case 3:
		frame->finished = true;
		return;

	default:
		return;
	}
}

inline simple_generator make_simple_generator_throw_after_yield() {
	trace_ramp(trace_mode::simple, "allocate throw-after-yield generator frame");
	auto* frame = new simple_generator_frame{};
	frame->resume_fn = simple_generator_throw_resume;
	frame->destroy_fn = simple_generator_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	return simple_generator{frame, false};
}

inline void simple_task_throw_after_await_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_task_int_frame*>(base);

	switch (frame->state_index) {
	case 0:
		trace_frame_case(trace_mode::simple, 0);
		trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_never");
		if (!frame->manual_awaitable.await_ready()) {
			if (frame->manual_awaitable.await_suspend(frame)) {
				frame->state_index = 1;
				return;
			}
		}
		frame->manual_awaitable.await_resume();
		trace_log(trace_mode::simple, "[Frame:throw]", "throw after co_await");
		frame->result.set_exception(std::make_exception_ptr(std::runtime_error("simple after await")));
		trace_log(trace_mode::simple, "[Promise:unhandled_exception]");
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "suspend_always");
		frame->state_index = 2;
		return;

	case 1:
		trace_frame_case(trace_mode::simple, 1);
		frame->manual_awaitable.await_resume();
		trace_log(trace_mode::simple, "[Frame:throw]", "throw after co_await");
		frame->result.set_exception(std::make_exception_ptr(std::runtime_error("simple after await")));
		trace_log(trace_mode::simple, "[Promise:unhandled_exception]");
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "suspend_always");
		frame->state_index = 2;
		return;

	case 2:
		frame->finished = true;
		return;

	default:
		return;
	}
}

inline simple_task<int> make_simple_task_throw_after_await() {
	trace_ramp(trace_mode::simple, "task ramp -- throw after co_await");
	auto* frame = new simple_task_int_frame{};
	frame->resume_fn = simple_task_throw_after_await_resume;
	frame->destroy_fn = simple_task_int_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_task<int>{frame};
}

inline native_throw_generator make_native_generator_throw_after_yield() {
	trace_ramp(trace_mode::native, "coroutine ramp -- throw after yield");
	auto gen = []() -> native_throw_generator {
		co_yield 1;
		trace_log(trace_mode::native, "[Frame:throw]", "throw after co_yield");
		throw std::runtime_error("native generator boom");
	}();
	return gen;
}

inline native_task<int> make_native_task_throw_after_await(std::coroutine_handle<>* handle_out) {
	trace_ramp(trace_mode::native, "task coroutine -- throw after co_await");
	auto task = [handle_out]() -> native_task<int> {
		manual_resume_awaitable awaitable{trace_mode::native, handle_out, nullptr};
		co_await awaitable;
		trace_log(trace_mode::native, "[Frame:throw]", "throw after co_await");
		throw std::runtime_error("native after await");
		co_return 0;
	}();
	return task;
}

inline void run_demo_07() {
	run_generator_demo(
		"7) Exception across suspend",
		[] {
			{
				auto gen = make_native_generator_throw_after_yield();
				trace_main(trace_mode::native, "generator throw after co_yield");
				gen.resume();
				if (!gen.done())
					std::println("{} [Main] yielded = {}", trace_mode_label(trace_mode::native), gen.value());
				gen.resume();
				std::println("{} [Main] generator done={}", trace_mode_label(trace_mode::native), gen.done());
			}
			{
				std::coroutine_handle<> stored{};
				auto task = make_native_task_throw_after_await(&stored);
				trace_main(trace_mode::native, "task throw after co_await");
				if (stored)
					stored.resume();
				try {
					(void)task.get();
				}
				catch (const std::exception& ex) {
					std::println("{} [Main] caught: {}", trace_mode_label(trace_mode::native), ex.what());
				}
			}
		},
		[] {
			{
				auto gen = make_simple_generator_throw_after_yield();
				trace_main(trace_mode::simple, "generator throw after co_yield");
				gen.resume();
				if (!gen.done())
					std::println("{} [Main] yielded = {}", trace_mode_label(trace_mode::simple), gen.value());
				gen.resume();
				std::println("{} [Main] generator done={}", trace_mode_label(trace_mode::simple), gen.done());
			}
			{
				auto task = make_simple_task_throw_after_await();
				simple_coroutine_frame* stored = simple_manual_await_target(task);
				trace_main(trace_mode::simple, "task throw after co_await");
				if (stored != nullptr)
					stored->resume();
				try {
					(void)task.get();
				}
				catch (const std::exception& ex) {
					std::println("{} [Main] caught: {}", trace_mode_label(trace_mode::simple), ex.what());
				}
			}
		});
}
#pragma endregion //MINE
