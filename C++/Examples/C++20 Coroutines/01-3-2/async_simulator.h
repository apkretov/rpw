#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"
#include <chrono>
#include <functional>
#include <optional>
#include <print>
#include <thread>
#include <type_traits>
#include <utility>

using namespace std::chrono_literals;

// Awaitable stand-in for network/database I/O: suspend the frame, run work on another thread after ~500ms, then resume.
// Same prints/timing as 01-3; await_suspend takes simple_coroutine_frame* instead of coroutine_handle.
template <typename Result>
struct async_awaitable {
	const char* name;
	std::function<Result()> work;
	std::optional<Result> result;

	bool await_ready() const noexcept { return false; }

	bool await_suspend(simple_coroutine_frame* continuation) {
		std::println("{} 333 {}: launching from thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
		std::jthread([this, continuation] {
			std::println("{} 444/555 {}: running on thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
			const auto start = std::chrono::steady_clock::now();
			std::this_thread::sleep_for(500ms);
			const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
			std::println("{} 888 {}: finished in {} ms on thread {}", std::this_thread::get_id(), name, ms, std::this_thread::get_id());
			result = work();
			continuation->resume();
		}).detach();
		return true;
	}

	Result await_resume() { return std::move(*result); }
};

template <>
struct async_awaitable<void> {
	const char* name;
	std::function<void()> work;

	bool await_ready() const noexcept { return false; }

	bool await_suspend(simple_coroutine_frame* continuation) {
		std::println("{} 333 {}: launching from thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
		std::jthread([this, continuation] {
			std::println("{} 444/555 {}: running on thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
			const auto start = std::chrono::steady_clock::now();
			std::this_thread::sleep_for(500ms);
			const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
			std::println("{} 888 {}: finished in {} ms on thread {}", std::this_thread::get_id(), name, ms, std::this_thread::get_id());
			work();
			continuation->resume();
		}).detach();
		return true;
	}

	void await_resume() {}
};

template <typename Work>
auto simulate_async(const char* name, Work work) {
	using result_type = std::invoke_result_t<Work>;
	if constexpr (std::is_void_v<result_type>)
		return async_awaitable<void>{name, std::function<void()>(std::move(work))};
	else
		return async_awaitable<result_type>{name, std::function<result_type()>(std::move(work))};
}
#pragma endregion //MINE
