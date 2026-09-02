#pragma region MINE
#pragma once

#include "demo_common.h"
#include "types/native_task.h"
#include "types/simple_task.h"
#include <stdexcept>

inline void simple_task_return_42_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_task_int_frame*>(base);

	switch (frame->state_index) {
	case 0:
		trace_frame_case(trace_mode::simple, 0);
		trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_never");
		trace_log(trace_mode::simple, "[Promise:return_value]", "42");
		frame->result.set_value(42);
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "suspend_always");
		frame->state_index = 1;
		return;

	case 1:
		trace_frame_case(trace_mode::simple, 1);
		frame->finished = true;
		return;

	default:
		return;
	}
}

inline void simple_task_throw_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_task_int_frame*>(base);

	switch (frame->state_index) {
	case 0:
		trace_frame_case(trace_mode::simple, 0);
		trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_never");
		trace_log(trace_mode::simple, "[Frame:throw]", "throw before co_return");
		frame->result.set_exception(std::make_exception_ptr(std::runtime_error("simple task boom")));
		trace_log(trace_mode::simple, "[Promise:unhandled_exception]", "stored in result");
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "suspend_always");
		frame->state_index = 1;
		return;

	case 1:
		frame->finished = true;
		return;

	default:
		return;
	}
}

inline simple_task<int> make_simple_task_return_42() {
	trace_ramp(trace_mode::simple, "task ramp -- return 42");
	auto* frame = new simple_task_int_frame{};
	frame->resume_fn = simple_task_return_42_resume;
	frame->destroy_fn = simple_task_int_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_task<int>{frame};
}

inline simple_task<int> make_simple_task_throw() {
	trace_ramp(trace_mode::simple, "task ramp -- throw path");
	auto* frame = new simple_task_int_frame{};
	frame->resume_fn = simple_task_throw_resume;
	frame->destroy_fn = simple_task_int_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_task<int>{frame};
}

inline native_task<int> make_native_task_return_42() {
	trace_ramp(trace_mode::native, "task coroutine -- return 42");
	auto task = []() -> native_task<int> {
		co_return 42;
	}();
	return task;
}

inline native_task<int> make_native_task_throw() {
	trace_ramp(trace_mode::native, "task coroutine -- throw path");
	auto task = []() -> native_task<int> {
		trace_log(trace_mode::native, "[Frame:throw]", "throw before co_return");
		throw std::runtime_error("native task boom");
		co_return 0;
	}();
	return task;
}

inline void run_demo_03() {
	run_generator_demo(
		"3) Task -- co_return value + exception",
		[] {
			{
				auto task = make_native_task_return_42();
				trace_main(trace_mode::native, "task.get()");
				int value = task.get();
				std::println("{} [Main] result = {}", trace_mode_label(trace_mode::native), value);
			}
			{
				auto task = make_native_task_throw();
				trace_main(trace_mode::native, "task.get() on throwing task");
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
				auto task = make_simple_task_return_42();
				trace_main(trace_mode::simple, "task.get()");
				int value = task.get();
				std::println("{} [Main] result = {}", trace_mode_label(trace_mode::simple), value);
			}
			{
				auto task = make_simple_task_throw();
				trace_main(trace_mode::simple, "task.get() on throwing task");
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
