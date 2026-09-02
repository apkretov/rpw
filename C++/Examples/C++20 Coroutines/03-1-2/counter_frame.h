#pragma once

#pragma region MINE

#include "awaiter.h"
#include "simple_coroutine_frame.h"

// Locals that would live in the compiler-generated counter coroutine frame.
struct counter_frame : simple_coroutine_frame {
	unsigned i = 0;
	Awaiter awaiter{};
	simple_coroutine_frame** handle_out = nullptr;
};
#pragma endregion //MINE
