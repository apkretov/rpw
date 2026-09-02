#pragma region MINE
#pragma once

#include "demo_common.h"

// Textbook flow (lazy generator, count_to(5)):
// count_to(5) returns  -> [Ramp] frame allocated, initial_suspend stops before body
// first next()         -> body runs to first co_yield
// co_yield i           -> [Promise:yield_value] stores i, co_await suspend_always pauses
// value()              -> reads promise.current_value
// next() again         -> resumes loop, co_yield next i
// after last yield     -> return_void, final_suspend keeps frame alive until destroy

inline simple_generator make_simple_generator_lazy() { return make_simple_count_to(5, true, true); }

inline native_generator<true> make_native_generator_lazy() { return count_to_native<true>(5); }

inline void run_demo_01() {
	// 1) Generator, lazy (initial_suspend=always, count_to(5), final_suspend=always)
	run_generator_demo(
		"1) Generator -- lazy start (initial_suspend=always, count_to(5))",
		[] {
			auto gen = make_native_generator_lazy();
			consume_generator_lazy_next(gen, trace_mode::native);
		},
		[] {
			auto gen = make_simple_generator_lazy();
			consume_generator_lazy_next(gen, trace_mode::simple);
		});
}
#pragma endregion //MINE
