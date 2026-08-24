#pragma once

#pragma region MINE

#include <algorithm>
#include <chrono>
#include <coroutine>
#include <optional>
#include <print>
#include <thread>
#include <type_traits>
#include <utility>

using namespace std::chrono_literals;

template<typename Work>
struct async_awaitable { // Awaitable stand-in for network/database I/O: suspend the coroutine, run work on another thread after ~500ms, then resume. Same timing model as 01-2's callbacks.
	using result_type = std::invoke_result_t<Work>;

	const char* name;
	Work work;
	std::optional<std::conditional_t<std::is_void_v<result_type>, char, result_type>> result;

	bool await_ready() const noexcept { return false; }

	void await_suspend(std::coroutine_handle<> continuation) {
		std::println("{} 333 {}: launching from thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
		std::jthread([this, continuation] {
			std::println("{} 444/555 {}: running on thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
			const auto start = std::chrono::steady_clock::now();
			std::this_thread::sleep_for(500ms);
			const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
			std::println("{} 888 {}: finished in {} ms on thread {}", std::this_thread::get_id(), name, ms, std::this_thread::get_id());
			if constexpr (std::is_void_v<result_type>)
				work();
			else
				result = work();
			continuation.resume();
		}).detach();
	}

	auto await_resume() {
		if constexpr (std::is_void_v<result_type>)
			return;
		else
			return std::move(*result);
	}
};

template<typename Work>
auto simulate_async(const char* name, Work work) {
	return async_awaitable<Work>{name, std::move(work)};
}
#pragma endregion //MINE
