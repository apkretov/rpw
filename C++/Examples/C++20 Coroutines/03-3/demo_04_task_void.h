#pragma region MINE
#pragma once

#include "demo_common.h"
#include "types/native_task.h"
#include "types/simple_task.h"

inline void simple_task_return_void_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_task_void_frame*>(base);

	switch (frame->state_index) {
	case 0:
		trace_frame_case(trace_mode::simple, 0);
		trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_never");
		trace_log(trace_mode::simple, "[Promise:return_void]");
		frame->result.set_value();
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

inline simple_task<void> make_simple_task_return_void() {
	trace_ramp(trace_mode::simple, "task ramp -- return void");
	auto* frame = new simple_task_void_frame{};
	frame->resume_fn = simple_task_return_void_resume;
	frame->destroy_fn = simple_task_void_destroy;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_task<void>{frame};
}

inline native_task<void> make_native_task_return_void() {
	trace_ramp(trace_mode::native, "task coroutine -- return void");
	auto task = []() -> native_task<void> {
		co_return;
	}();
	return task;
}

inline void run_demo_04() {
	run_generator_demo(
		"4) Task -- co_return void",
		[] {
			auto task = make_native_task_return_void();
			trace_main(trace_mode::native, "task.get()");
			task.get();
			std::println("{} [Main] void task completed", trace_mode_label(trace_mode::native));
		},
		[] {
			auto task = make_simple_task_return_void();
			trace_main(trace_mode::simple, "task.get()");
			task.get();
			std::println("{} [Main] void task completed", trace_mode_label(trace_mode::simple));
		});
}
#pragma endregion //MINE
