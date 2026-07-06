#pragma region MINE
#pragma once

#include "simple_packaged_task.h"
#include <thread>
#include <type_traits>
using namespace std;

template <typename F, typename... Args> 
auto simple_async(F&& f, Args&&... args) { // A very simple async that always launches a new thread (like launch::async). It builds a packaged_task, gets its future, moves the task into a thread, and returns the future.
	using R = invoke_result_t<F, Args...>;

	auto bound = bind_front(forward<F>(f), forward<Args>(args)...); // We bind f and args into a zero-arg callable for our packaged_task<R()>.

	simple_packaged_task<R()> task(move(bound));
	auto fut = task.get_future();

	jthread t(move(task)); // Move the task into a background thread.
	t.detach(); // fire-and-forget; future still sees the result

	return fut;
}
#pragma endregion //MINE