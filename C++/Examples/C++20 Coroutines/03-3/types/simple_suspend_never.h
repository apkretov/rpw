#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/trace.h"

struct simple_suspend_never { // Traced awaitable modeling std::suspend_never in simple code.
	bool await_ready() const {
		trace_log(trace_mode::simple, "[Awaitable:await_ready]", "true");
		return true;
	}

	bool await_suspend(simple_coroutine_frame*) {
		trace_log(trace_mode::simple, "[Awaitable:await_suspend]", "(skipped -- already ready)");
		return false;
	}

	void await_resume() const {
		trace_log(trace_mode::simple, "[Awaitable:await_resume]");
	}
};
#pragma endregion //MINE
