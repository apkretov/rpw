#pragma region MINE
#pragma once

#include "types/trace.h"
#include <coroutine>

struct native_throw_generator;

struct native_throw_generator_promise {
	int current_value = 0;
	bool done = false;

	native_throw_generator get_return_object();

	std::suspend_always initial_suspend() noexcept {
		trace_log(trace_mode::native, "[Promise:initial_suspend]", "suspend_always");
		return {};
	}

	auto final_suspend() noexcept {
		struct awaiter {
			bool await_ready() const noexcept { return false; }
			void await_suspend(std::coroutine_handle<>) const noexcept {}
			void await_resume() const noexcept {}
		};
		return awaiter{};
	}

	std::suspend_always yield_value(int value) {
		trace_log(trace_mode::native, "[Promise:yield_value]", "1");
		current_value = value;
		return {};
	}

	void unhandled_exception() {
		trace_log(trace_mode::native, "[Promise:unhandled_exception]");
		done = true;
	}

	void return_void() { done = true; }
};
#pragma endregion //MINE
