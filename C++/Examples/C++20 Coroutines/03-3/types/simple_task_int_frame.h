#pragma region MINE
#pragma once

#include "types/simple_coroutine_frame.h"
#include "types/simple_coroutine_result.h"
#include "types/simple_manual_awaitable.h"
#include <memory>

struct simple_task_int_frame : simple_coroutine_frame {
	simple_coroutine_result<int> result{};
	simple_manual_awaitable manual_awaitable{};
	std::unique_ptr<simple_task_int_frame> nested_inner{};
	int nested_value = 0;
	bool throw_after_await = false;
};

inline void simple_task_int_destroy(simple_coroutine_frame* base) {
	delete static_cast<simple_task_int_frame*>(base);
}
#pragma endregion //MINE
