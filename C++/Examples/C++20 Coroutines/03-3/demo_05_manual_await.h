#pragma region MINE
#pragma once

#include "demo_common.h"
#include "types/manual_resume_awaitable.h"
#include "types/native_task.h"
#include "types/simple_task.h"
#include <coroutine>

inline void simple_task_manual_await_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_task_void_frame*>(base);

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
		trace_log(trace_mode::simple, "[Promise:return_void]");
		frame->result.set_value();
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "suspend_always");
		frame->state_index = 2;
		return;

	case 1:
		trace_frame_case(trace_mode::simple, 1);
		frame->manual_awaitable.await_resume();
		trace_log(trace_mode::simple, "[Promise:return_void]");
		frame->result.set_value();
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

inline simple_task<void> make_simple_task_manual_await() {
	trace_ramp(trace_mode::simple, "task ramp -- manual await");
	auto* frame = new simple_task_void_frame{};
	frame->resume_fn = simple_task_manual_await_resume;
	frame->destroy_fn = simple_task_void_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_task<void>{frame};
}

inline native_task<void> make_native_task_manual_await(std::coroutine_handle<>* handle_out) {
	trace_ramp(trace_mode::native, "task coroutine -- manual await");
	auto task = [handle_out]() -> native_task<void> {
		manual_resume_awaitable awaitable{trace_mode::native, handle_out, nullptr};
		co_await awaitable;
		co_return;
	}();
	return task;
}

inline void run_demo_05() {
	run_generator_demo(
		"5) Custom awaitable -- manual resume",
		[] {
			std::coroutine_handle<> stored{};
			auto task = make_native_task_manual_await(&stored);
			trace_main(trace_mode::native, "manual resume of stored handle");
			if (stored)
				stored.resume();
			task.get();
		},
		[] {
			auto task = make_simple_task_manual_await();
			simple_coroutine_frame* stored = simple_manual_await_target(task);
			trace_main(trace_mode::simple, "manual resume of stored frame");
			if (stored != nullptr)
				stored->resume();
			task.get();
		});
}
#pragma endregion //MINE
