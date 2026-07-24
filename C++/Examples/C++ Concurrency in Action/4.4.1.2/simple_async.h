#pragma region MINE
#pragma once

#include "simple_packaged_task.h"
#include <algorithm>
#include <functional>
#include <thread>
#include <type_traits>
#include <utility>

template <typename F, typename... Args> 
auto simple_async(F&& f, Args&&... args) { // A very simple async that always launches a new thread (like launch::async). It builds a packaged_task, gets its future, moves the task into a thread, and returns the future.
	using R = std::invoke_result_t<F, Args...>;

	auto bound = std::bind_front(std::forward<F>(f), std::forward<Args>(args)...); // We bind f and args into a zero-arg callable for our packaged_task<R()>.

	simple_packaged_task<R()> task(std::move(bound));
	auto fut = task.get_future();

	std::jthread t(std::move(task)); // Move the task into a background thread.
	t.detach(); // fire-and-forget; future still sees the result

	return fut;
}
#pragma endregion //MINE