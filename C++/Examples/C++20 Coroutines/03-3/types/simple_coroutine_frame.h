#pragma region MINE
#pragma once

#include "types/trace.h"
#include <cstddef>

struct simple_coroutine_frame {
	int state_index = 0;
	bool finished = false;

	void (*resume_fn)(simple_coroutine_frame*) = nullptr;
	void (*destroy_fn)(simple_coroutine_frame*) = nullptr;

	void resume() {
		if (finished || resume_fn == nullptr)
			return;
		trace_log(trace_mode::simple, "[Frame:resume]", "enter resume_fn");
		resume_fn(this);
	}

	void destroy() {
		if (destroy_fn == nullptr)
			return;
		trace_log(trace_mode::simple, "[Frame:destroy]", "call destroy_fn");
		destroy_fn(this);
		destroy_fn = nullptr;
		resume_fn = nullptr;
	}
};
#pragma endregion //MINE
