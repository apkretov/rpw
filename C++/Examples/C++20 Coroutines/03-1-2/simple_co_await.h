#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"

// Models co_await expansion: ready -> suspend (save state, return) -> resume label -> resume.
template <typename awaitable_t>
inline bool simple_co_await(simple_coroutine_frame* frame, int resume_state, awaitable_t& awaitable, auto&& on_resume_body) {
	if (awaitable.await_ready())
		return false;

	if (awaitable.await_suspend(frame)) {
		frame->state_index = resume_state;
		return true;
	}

	on_resume_body();
	awaitable.await_resume();
	return false;
}
#pragma endregion //MINE
