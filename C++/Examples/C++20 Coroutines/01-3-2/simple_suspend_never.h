#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"

// Models std::suspend_never for the hand-rolled state machine (initial_suspend = never).
struct simple_suspend_never {
	bool await_ready() const noexcept { return true; }
	bool await_suspend(simple_coroutine_frame*) noexcept { return false; }
	void await_resume() const noexcept {}
};
#pragma endregion //MINE
