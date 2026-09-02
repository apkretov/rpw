#pragma region MINE
#pragma once

#include "types/native_generator.h"
#include "types/simple_co_await.h"
#include "types/simple_generator.h"
#include "types/simple_suspend_always.h"
#include "types/simple_suspend_never.h"
#include "types/trace.h"
#include <new>
#include <print>

inline void run_generator_demo(const char* title, auto&& run_native, auto&& run_simple) {
	std::println("\n=== {} ===", title);
	std::println("--- Native ---");
	run_native();
	std::println("--- Simple ---");
	run_simple();
}

inline void consume_generator_lazy_next(auto& gen, trace_mode mode) {
	trace_main(mode, "while (gen.next()) { value = gen.value(); }");
	while (gen.next()) {
		std::println("{} [Main] value = {}", trace_mode_label(mode), gen.value());
	}
	gen.destroy();
}

inline void consume_generator_eager_next(auto& gen, trace_mode mode) {
	trace_main(mode, "eager -- first value ready at ramp, then next() loop");
	if (!gen.done())
		std::println("{} [Main] value = {} (ready before first next())",
			trace_mode_label(mode), gen.value());
	while (gen.next()) {
		std::println("{} [Main] value = {}", trace_mode_label(mode), gen.value());
	}
	gen.destroy();
}

inline void consume_generator_no_yield_suspend(auto& gen, trace_mode mode) {
	trace_main(mode, "single next() -- suspend_never yields run whole loop");
	gen.next();
	std::println("{} [Main] value = {} (only last value survives)",
		trace_mode_label(mode), gen.value());
	gen.destroy();
}

// Shared count_to state machine -- used by demos 1 / 1b / 2.
inline void simple_generator_destroy(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_generator_frame*>(base);
	trace_ramp(trace_mode::simple, "destroy frame (operator delete)");
	delete frame;
}

inline void simple_count_to_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<simple_generator_frame*>(base);
resume_switch:
	switch (frame->state_index) {
	case 0: {
		trace_frame_case(trace_mode::simple, 0);
		if (frame->lazy_start) {
			trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_always -- body not run at ramp");
			simple_suspend_always initial{};
			if (simple_co_await(frame, 1, initial, [] {}))
				return;
		} else
			trace_log(trace_mode::simple, "[Promise:initial_suspend]", "suspend_never -- run body before ramp returns");
		frame->state_index = 1;
		[[fallthrough]];
	}

	case 1: {
		trace_frame_case(trace_mode::simple, 1);
		if (frame->i > frame->n)
			goto do_return;

		frame->promise.yield_value(frame->i, frame->yield_suspends);
		if (frame->yield_suspends) {
			simple_suspend_always yield_await{};
			if (simple_co_await(frame, 2, yield_await, [] {}))
				return;
		} else {
			simple_suspend_never yield_await{};
			simple_co_await(frame, 2, yield_await, [] {});
		}
		frame->state_index = 2;
		[[fallthrough]];
	}

	case 2: {
		trace_frame_case(trace_mode::simple, 2);
		++frame->i;
		frame->state_index = 1;
		goto resume_switch;
	}

	do_return:
	case 3: {
		trace_frame_case(trace_mode::simple, 3);
		frame->promise.return_void();
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "co_await suspend_always -- frame kept alive");
		simple_suspend_always final_await{};
		if (simple_co_await(frame, 4, final_await, [] {}))
			return;
		frame->at_final_suspend = true;
		frame->state_index = 4;
		[[fallthrough]];
	}

	case 4: {
		trace_frame_case(trace_mode::simple, 4);
		trace_log(trace_mode::simple, "[Promise:final_suspend]", "resumed at destroy");
		frame->finished = true;
		return;
	}

	default:
		return;
	}
}

inline simple_generator make_simple_count_to(int n, bool lazy_start, bool yield_suspends) {
	if (lazy_start)
		trace_ramp(trace_mode::simple, "allocate frame; count_to -- initial_suspend=always");
	else
		trace_ramp(trace_mode::simple, "allocate frame; count_to -- initial_suspend=never");
	auto* frame = new simple_generator_frame{};
	frame->resume_fn = simple_count_to_resume;
	frame->destroy_fn = simple_generator_destroy;
	frame->n = n;
	frame->i = 1;
	frame->lazy_start = lazy_start;
	frame->yield_suspends = yield_suspends;
	trace_log(trace_mode::simple, "[Promise:get_return_object]");
	frame->resume();
	return simple_generator{frame, !lazy_start};
}

template <bool lazy_start, bool yield_suspends = true>
inline native_generator<lazy_start, yield_suspends> count_to_impl(int stop_at) {
	for (int i = 1; i <= stop_at; ++i)
		co_yield i;
}

template <bool lazy_start>
inline native_generator<lazy_start> count_to_native(int n) {
	trace_ramp(trace_mode::native, lazy_start ? "count_to -- initial_suspend=always" : "count_to -- initial_suspend=never");
	return count_to_impl<lazy_start>(n);
}

template <bool lazy_start>
inline native_generator<lazy_start, false> count_to_native_no_yield_suspend(int n) {
	trace_ramp(trace_mode::native, "count_to -- yield_value returns suspend_never");
	return count_to_impl<lazy_start, false>(n);
}
#pragma endregion //MINE
