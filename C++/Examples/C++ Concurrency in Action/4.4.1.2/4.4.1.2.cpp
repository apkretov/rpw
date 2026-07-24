#pragma region MINE

#include <chrono>
#include <exception>
#include <iostream>
#include <thread>
#include <utility>
#include "simple_future.h"
#include "simple_packaged_task.h"
#include "simple_promise.h"
#include "../../stdafx.h"
#define SIMPLE_ASYNC // Comment this line to use spawn_task instead of simple_async.
#ifdef SIMPLE_ASYNC
#include "simple_async.h"  
#else //SPAWN_TASK
#include "Listing 4.14.h"
#endif //SPAWN_TASK

static int compute_sum(int a, int b) { // A simple function to run asynchronously.
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return a + b;
}

int main() {
	print_file_line();

	{ // 1) Manual promise/future usage.
		simple_promise<int> p;
		simple_future<int> f = p.get_future();

		std::jthread producer([pr = std::move(p)]() mutable {
			try {
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simulate work
				pr.set_value(compute_sum(10, 32));
			}
			catch (...) {
				pr.set_exception(std::current_exception());
			}
		});

		int result = f.get(); // In the main thread, wait and get the result.
		std::cout << "simple_promise/simple_future result = " << result << "\n";
	}

	{ // 2) Using packaged_task directly.
		simple_packaged_task<int(int, int)> task(compute_sum);
		auto f = task.get_future();

		std::jthread t(std::move(task), 10, 32); // task(10, 32) runs in the new thread and sets the promise.

		int result = f.get();
		std::cout << "simple_packaged_task result = " << result << "\n";
	}

	{ // 3) Using async-like helper.
#ifdef SIMPLE_ASYNC
		auto f = simple_async(compute_sum, 10, 32); // compute_sum(7, 8) runs in background; we just wait on the future.
#else //SPAWN_TASK
		auto f = spawn_task( [](std::pair<int, int> args) { return compute_sum(args.first, args.second); }, std::pair{10, 32}); // spawn_task (Listing 4.14) passes one argument to f; bundle (10, 32) for compute_sum.
#endif //SPAWN_TASK
		int result = f.get();
		std::cout << "simple_async result = " << result << "\n";
	}

	return 0;
}

/*
Below is a concise, well-cited explanation of how std::future / std::promise / std::packaged_task relate, how the shared state is implemented and synchronized in practice, and a small self-contained illustrative implementation (not copy-paste of any standard library) that shows the essential mechanics. Each factual sentence below cites sources that describe the standard design or typical implementations.

Direct answer
* std::future does not itself create a thread; it represents the consumer handle to a shared state that is fulfilled by a corresponding producer (for example a std::promise, a std::packaged_task, or the implementation of std::async).
* std::promise is the producer API that sets the value or exception into that shared state; std::future is the consumer API that waits for and retrieves it.
* Implementations typically implement the communication via a small shared-state object (created when get_future is called) and use synchronization primitives and/or atomics plus a wait/notify mechanism to make wait()/get() block until the state is ready; this is not a single trivial std::condition_variable necessarily owned by promise - the standard leaves details open and many implementations use a compact custom wait/notify inside the shared state rather than a plain condition_variable object per promise.

Key concepts (short)

Shared state and roles
* The shared state is an object created when the future is obtained from promise/packaged_task; it stores either the value or an exception, plus flags that mark "ready" and bookkeeping for who is waiting.
* The promise (or packaged_task when it fulfills its promise) writes the result or exception into that shared state; the future reads it or blocks until it becomes ready.

Synchronization and wakeup
* The standard requires future::get / wait to block until ready, but it does not mandate a specific primitive; implementations commonly use a small wait-list plus a condition-like wake mechanism or atomics with platform-specific wait/notify (futex or Windows WaitOnAddress) to efficiently park and wake threads.
* Some proposals and implementations aim to reduce heavy-weight locks by using atomics and specialized wait primitives (for example futex-like waits or semaphores) to avoid allocating a std::condition_variable for every shared state.

About std::packaged_task and std::async

Packaged_task
* std::packaged_task is a wrapper around a callable that owns or is associated with a promise/shared state; calling operator() runs the callable and stores the result (or exception) into the shared state so that the associated future becomes ready.
* std::async typically creates a packaged_task + thread (or schedules on an executor), or defers execution until get() if std::launch::deferred is selected.

Minimal illustrative implementation
The following is a compact educational implementation that demonstrates the core mechanics (shared state, promise, future, packaged_task). It is intentionally simplified: it omits copy/move edge cases, allocator/exception-safety corner-cases, and many standard features (no then/continuations, no timed waits, no reference result types). It uses a mutex + condition_variable for clarity (real standard libraries may use more optimized primitives).

Code (conceptual - compile/test before production use)
* shared_state<T> holds the optional value or exception, a ready flag, a mutex and a condition_variable.
* promise<T> moves a pointer to shared_state and provides set_value / set_exception / get_future.
* future<T> holds the same shared_state pointer and implements get() that waits on the condition_variable until ready and then returns or rethrows the exception.
* packaged_task wraps a callable and a shared_state; calling operator() runs the callable and sets the value/exception.

Example code (short, illustrative):

* shared_state<T>:
o members: std::mutex m; std::condition_variable cv; bool ready = false; std::variant<std::monostate, T, std::exception_ptr> storage;
o methods: set_value(T), set_exception(exception_ptr), wait_until_ready(), get_value_or_throw().

* promise<T>:
o get_future(): returns future<T> with pointer to shared_state.
o set_value / set_exception: call the corresponding shared_state methods.

* future<T>:
o get(): lock shared_state, wait on cv until ready, then return value or rethrow exception.

* packaged_task<F>: stores callable f and the shared_state produced by get_future(); operator() executes f and forwards result to set_value or captures exception and calls set_exception.
*/
#pragma endregion //MINE
