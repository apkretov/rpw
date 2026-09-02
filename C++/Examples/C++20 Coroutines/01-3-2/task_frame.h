#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"
#include <condition_variable>
#include <exception>
#include <mutex>

// Completion model mirrors 01-3's promise (mutex/cv/done) on a hand-rolled frame instead of coroutine_handle.
struct task_frame : simple_coroutine_frame {
	std::mutex mutex;
	std::condition_variable cv;
	bool done = false;
	std::exception_ptr exception;
};
#pragma endregion //MINE
