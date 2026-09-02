#pragma region MINE
#pragma once

#include "types/native_coroutine_result.h"
#include "types/trace.h"
#include <coroutine>
#include <exception>
#include <memory>

template <typename T>
class native_task;

struct native_task_void_promise {
	std::shared_ptr<native_coroutine_result<void>> result =
		std::make_shared<native_coroutine_result<void>>();

	native_task<void> get_return_object();

	std::suspend_never initial_suspend() noexcept {
		trace_log(trace_mode::native, "[Promise:initial_suspend]", "suspend_never");
		return {};
	}

	auto final_suspend() noexcept {
		struct awaiter {
			bool await_ready() const noexcept { return false; }
			void await_suspend(std::coroutine_handle<>) const noexcept {
				trace_log(trace_mode::native, "[Promise:final_suspend]", "suspend_always -- frame kept alive");
			}
			void await_resume() const noexcept {}
		};
		return awaiter{};
	}

	void return_void() {
		trace_log(trace_mode::native, "[Promise:return_void]");
		result->set_value();
	}

	void unhandled_exception() {
		trace_log(trace_mode::native, "[Promise:unhandled_exception]");
		result->set_exception(std::current_exception());
	}
};
#pragma endregion //MINE
