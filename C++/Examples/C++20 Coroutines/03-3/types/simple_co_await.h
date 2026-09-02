#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/trace.h"

template <typename awaitable_t>
inline bool simple_co_await(simple_coroutine_frame* frame, int resume_state, awaitable_t& awaitable, auto&& on_resume_body) { // Models co_await expansion: ready -> suspend (save state, return) -> resume label -> resume.
	if (awaitable.await_ready())
		return false;

	if (awaitable.await_suspend(frame)) {
		trace_frame_state_index(trace_mode::simple, resume_state);
		frame->state_index = resume_state;
		return true;
	}

	on_resume_body();
	awaitable.await_resume();
	return false;
}
#pragma endregion //MINE
