#pragma region MINE
#pragma once

#include "demo_common.h"

inline simple_generator make_simple_generator_eager() {
	return make_simple_count_to(5, false, true);
}

inline native_generator<false> make_native_generator_eager() {
	return count_to_native<false>(5);
}

inline void run_demo_02() {
	run_generator_demo(
		"2) Generator -- eager start (initial_suspend=never, count_to(5))",
		[] {
			auto gen = make_native_generator_eager();
			consume_generator_eager_next(gen, trace_mode::native);
		},
		[] {
			auto gen = make_simple_generator_eager();
			consume_generator_eager_next(gen, trace_mode::simple);
		});
}
#pragma endregion //MINE
