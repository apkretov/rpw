#pragma once

#pragma region MINE

#include "awaiter.h"
#include "simple_coroutine_frame.h"

struct counter_frame : simple_coroutine_frame { // Locals that would live in the compiler-generated counter coroutine frame.
	unsigned i = 0;
	Awaiter awaiter{};
	simple_coroutine_frame** handle_out = nullptr;
};
#pragma endregion //MINE
