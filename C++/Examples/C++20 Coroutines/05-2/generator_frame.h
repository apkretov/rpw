#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"

// Locals that would live in the compiler-generated count_to coroutine frame.
struct generator_frame : simple_coroutine_frame {
	int i = 0;
	int n = 0;
	int current_value = 0;
};
#pragma endregion //MINE
