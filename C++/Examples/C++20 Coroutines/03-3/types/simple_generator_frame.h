#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/simple_generator_promise.h"

struct simple_generator_frame : simple_coroutine_frame {
	simple_generator_promise promise{};
	bool at_final_suspend = false;
	int n = 0;
	int i = 1;
	bool lazy_start = true;
	bool yield_suspends = true;
};
#pragma endregion //MINE
