#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"

// Models std::suspend_always for the hand-rolled state machine.
struct simple_suspend_always {
	bool await_ready() const noexcept { return false; }
	bool await_suspend(simple_coroutine_frame*) noexcept { return true; }
	void await_resume() const noexcept {}
};
#pragma endregion //MINE
