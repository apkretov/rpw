#pragma region MINE
#pragma once

#include "demo_common.h"

// Textbook flow (yield_value returns suspend_never -- demo 1b):
// first next()         -> entire loop runs in one resume (no pause at each yield)
// value()              -> only last value (5) remains in promise.current_value

inline simple_generator make_simple_generator_no_yield_suspend() {
	return make_simple_count_to(5, true, false);
}

inline native_generator<true, false> make_native_generator_no_yield_suspend() {
	return count_to_native_no_yield_suspend<true>(5);
}

inline void run_demo_01b() {
	run_generator_demo(
		"1b) Generator -- yield_value returns suspend_never (counterexample)",
		[] {
			auto gen = make_native_generator_no_yield_suspend();
			consume_generator_no_yield_suspend(gen, trace_mode::native);
		},
		[] {
			auto gen = make_simple_generator_no_yield_suspend();
			consume_generator_no_yield_suspend(gen, trace_mode::simple);
		});
}
#pragma endregion //MINE
