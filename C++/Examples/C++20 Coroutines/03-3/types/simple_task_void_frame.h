#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/simple_coroutine_result.h"
#include "types/simple_manual_awaitable.h"

struct simple_task_void_frame : simple_coroutine_frame {
	simple_coroutine_result<void> result{};
	simple_manual_awaitable manual_awaitable{};
};

inline void simple_task_void_destroy(simple_coroutine_frame* base) {
	delete static_cast<simple_task_void_frame*>(base);
}
#pragma endregion //MINE
