#pragma region MINE
#pragma once

#include "types/trace.h"
#include <print>

struct simple_generator_promise {
	int current_value = 0;
	bool done = false;

	void yield_value(int value, bool yield_suspends) {
		if (yield_suspends)
			std::println("{} [Promise:yield_value] {} -> co_await suspend_always", trace_mode_label(trace_mode::simple), value);
		else
			std::println("{} [Promise:yield_value] {} -> suspend_never -- loop continues without pausing", trace_mode_label(trace_mode::simple), value);
		current_value = value;
	}

	void return_void() {
		trace_log(trace_mode::simple, "[Promise:return_void]");
		done = true;
	}

	void unhandled_exception() {
		trace_log(trace_mode::simple, "[Promise:unhandled_exception]");
		done = true;
	}
};
#pragma endregion //MINE
