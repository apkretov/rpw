#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/trace.h"
#include <coroutine>

// Custom awaitable: await_suspend stores the awaiting coroutine; caller resumes manually.
struct manual_resume_awaitable {
	trace_mode mode = trace_mode::native;
	std::coroutine_handle<>* handle_out = nullptr;
	simple_coroutine_frame** simple_frame_out = nullptr;

	bool await_ready() const {
		trace_log(mode, "[Awaitable:await_ready]", "false");
		return false;
	}

	void await_suspend(std::coroutine_handle<> handle) const {
		trace_log(mode, "[Awaitable:await_suspend]", "store handle for manual resume");
		if (handle_out != nullptr)
			*handle_out = handle;
	}

	void await_resume() const {
		trace_log(mode, "[Awaitable:await_resume]");
	}
};
#pragma endregion //MINE
