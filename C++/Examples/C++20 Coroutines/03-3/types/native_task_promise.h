#pragma region MINE
#pragma once

#include "types/native_coroutine_result.h"
#include "types/trace.h"
#include <coroutine>
#include <exception>
#include <memory>
#include <utility>

template <typename T>
class native_task;

template <typename T>
struct native_task_promise {
	std::shared_ptr<native_coroutine_result<T>> result =
		std::make_shared<native_coroutine_result<T>>();

	native_task<T> get_return_object();

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

	void return_value(const T& v) {
		trace_log(trace_mode::native, "[Promise:return_value]");
		result->set_value(v);
	}

	void return_value(T&& v) {
		trace_log(trace_mode::native, "[Promise:return_value]");
		result->set_value(std::move(v));
	}

	void unhandled_exception() {
		trace_log(trace_mode::native, "[Promise:unhandled_exception]", "stored in result");
		result->set_exception(std::current_exception());
	}
};
#pragma endregion //MINE
