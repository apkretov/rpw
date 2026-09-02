#pragma region MINE
#pragma once

#include "types/trace.h"
#include <coroutine>
#include <print>

template <bool lazy_start, bool yield_suspends>
struct native_generator;

template <bool lazy_start, bool yield_suspends = true>
struct native_generator_promise {
	int current_value = 0;
	bool done = false;

	native_generator<lazy_start, yield_suspends> get_return_object();

	auto initial_suspend() noexcept {
		trace_log(trace_mode::native, "[Promise:initial_suspend]", lazy_start ? "suspend_always" : "suspend_never");
		if constexpr (lazy_start)
			return std::suspend_always{};
		else
			return std::suspend_never{};
	}

	auto final_suspend() noexcept {
		struct awaiter {
			bool await_ready() const noexcept {
				trace_log(trace_mode::native, "[Awaitable:await_ready]", "false");
				return false;
			}

			void await_suspend(std::coroutine_handle<>) const noexcept {
				trace_log(trace_mode::native, "[Awaitable:await_suspend]");
				trace_log(trace_mode::native, "[Promise:final_suspend]", "suspend_always -- frame kept alive");
			}

			void await_resume() const noexcept {
				trace_log(trace_mode::native, "[Awaitable:await_resume]");
				trace_log(trace_mode::native, "[Promise:final_suspend]", "resumed at destroy");
			}
		};
		return awaiter{};
	}

	auto yield_value(int value) {
		if constexpr (yield_suspends)
			std::println("{} [Promise:yield_value] {} -> suspend_always", trace_mode_label(trace_mode::native), value);
		else
			std::println("{} [Promise:yield_value] {} -> suspend_never -- loop continues without pausing", trace_mode_label(trace_mode::native), value);
		current_value = value;
		if constexpr (yield_suspends)
			return std::suspend_always{};
		else
			return std::suspend_never{};
	}

	void return_void() {
		trace_log(trace_mode::native, "[Promise:return_void]");
		done = true;
	}

	void unhandled_exception() {
		trace_log(trace_mode::native, "[Promise:unhandled_exception]");
		done = true;
	}
};
#pragma endregion //MINE
