#pragma region MINE
#pragma once

#include "demo_common.h"
#include "types/native_task.h"
#include "types/simple_task.h"

// Inner return-42 resume used by nested co_await (mirrors demo 03's return path).
inline void simple_task_nested_inner_return_42_resume(simple_coroutine_frame* base) {
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

inline void simple_task_nested_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_task_int_frame*>(base);

	switch (frame->state_index) {
	case 0:
		trace_frame_case(trace_mode::simple, 0);
		trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_never");
		trace_log(trace_mode::simple, "[Frame:co_await]", "inner task -- ramp nested frame");
		frame->nested_inner = std::make_unique<simple_task_int_frame>();
		frame->nested_inner->resume_fn = simple_task_nested_inner_return_42_resume;
		frame->nested_inner->destroy_fn = simple_task_int_destroy;
		frame->nested_inner->resume();
		frame->nested_value = frame->nested_inner->result.get();
		trace_log(trace_mode::simple, "[Awaitable:await_resume]", "nested value received");
		trace_log(trace_mode::simple, "[Promise:return_value]", "84");
		frame->result.set_value(frame->nested_value * 2);
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

inline simple_task<int> make_simple_task_nested() {
	trace_ramp(trace_mode::simple, "task ramp -- nested co_await inner");
	auto* frame = new simple_task_int_frame{};
	frame->resume_fn = simple_task_nested_resume;
	frame->destroy_fn = simple_task_int_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_task<int>{frame};
}

inline native_task<int> make_native_inner_task_42() {
	auto task = []() -> native_task<int> {
		co_return 42;
	}();
	return task;
}

inline native_task<int> make_native_task_nested() {
	trace_ramp(trace_mode::native, "task coroutine -- nested co_await inner");
	auto task = []() -> native_task<int> {
		trace_log(trace_mode::native, "[Frame:co_await]", "inner task");
		int inner = co_await make_native_inner_task_42();
		co_return inner * 2;
	}();
	return task;
}

inline void run_demo_06() {
	run_generator_demo(
		"6) Nested co_await -- inner task from outer",
		[] {
			auto task = make_native_task_nested();
			trace_main(trace_mode::native, "task.get()");
			int value = task.get();
			std::println("{} [Main] nested result = {}", trace_mode_label(trace_mode::native), value);
		},
		[] {
			auto task = make_simple_task_nested();
			trace_main(trace_mode::simple, "task.get()");
			int value = task.get();
			std::println("{} [Main] nested result = {}", trace_mode_label(trace_mode::simple), value);
		});
}
#pragma endregion //MINE
