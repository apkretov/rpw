#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/trace.h"

// Simple-side awaitable used inside hand-written state machines (no coroutine_handle).
struct simple_manual_awaitable {
	trace_mode mode = trace_mode::simple;
	simple_coroutine_frame* stored_frame = nullptr;

	bool await_ready() const {
		trace_log(mode, "[Awaitable:await_ready]", "false");
		return false;
	}

	// Returns true when the caller must suspend (always for this teaching awaitable).
	bool await_suspend(simple_coroutine_frame* caller) {
		trace_log(mode, "[Awaitable:await_suspend]", "store frame for manual resume");
		stored_frame = caller;
		return true;
	}

	void await_resume() const {
		trace_log(mode, "[Awaitable:await_resume]");
	}
};
#pragma endregion //MINE
