#pragma region MINE

#include "simple_awaitable.h"
#include "simple_task.h"
#include "../../stdafx.h"

#include <chrono>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <thread>

// 1) Basic co_return — like promise.set_value + future.get
static simple_task<int> compute_sum(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	co_return a + b; // → promise_type::return_value ≈ set_value
}

// 2) Exception path — unhandled_exception ≈ set_exception
static simple_task<int> compute_failing() {
	throw std::runtime_error("boom from coroutine");
	co_return 0; // unreachable; keeps this a coroutine returning int
}

// 3) co_await a teaching awaitable (suspend / resume without blocking get()'s CV wait
//    on the coroutine's behalf — the *caller* may still block on .get())
static simple_task<int> compute_with_delay(int a, int b) {
	std::cout << "compute_with_delay: before co_await resume_after\n";
	co_await resume_after{100ms};
	std::cout << "compute_with_delay: after resume_after (may be another thread)\n";
	co_await resume_on_new_thread{};
	std::cout << "compute_with_delay: after resume_on_new_thread\n";
	co_return a + b;
}

// 4) Nested / chained await of another task
static simple_task<int> compute_nested(int a, int b) {
	int partial = co_await compute_sum(a, b); // await another simple_task
	co_await resume_after{30ms};
	co_return partial * 2;
}

int main() {
	print_file_line();

	{ // 1) Basic coroutine that co_returns a value; caller gets it (≈ promise/future).
		auto t = compute_sum(10, 32);
		int result = t.get();
		std::cout << "basic co_return result = " << result << "\n";
	}

	{ // 2) Exception path (unhandled_exception ≈ set_exception; get rethrows).
		auto t = compute_failing();
		try {
			(void)t.get();
			std::cout << "unexpected: no exception\n";
		}
		catch (const std::exception& e) {
			std::cout << "exception path: " << e.what() << "\n";
		}
	}

	{ // 3) co_await teaching awaitables (suspend/resume vs CV wait).
		auto t = compute_with_delay(10, 32);
		int result = t.get();
		std::cout << "awaitable path result = " << result << "\n";
	}

	{ // 4) Chaining: co_await another simple_task.
		auto t = compute_nested(10, 32);
		int result = t.get();
		std::cout << "nested task result = " << result << "\n";
	}

	return 0;
}

/*
Futures (4.4.1.2) ↔ coroutines (this folder) — teaching map
----------------------------------------------------------
shared_state.h          ↔  simple_coro_state.h
  value / exception         result / exception
  ready + mutex + cv        ready + mutex + cv (+ optional continuation handle)
  (no frame)                real frame ALSO has locals + resume PC (not modeled here)

simple_promise.h        ↔  promise_type inside simple_task.h
  get_future()              get_return_object()
  set_value(...)            return_value(...) / return_void()
  set_exception(...)        unhandled_exception()
  (N/A)                     initial_suspend / final_suspend

simple_future.h         ↔  simple_task (return object)
  get() / wait()            get() / wait()   — block the thread on the CV
  (N/A)                     also awaitable: co_await parks the coroutine instead

simple_packaged_task /  ↔  the coroutine function body itself
simple_async                (compiler builds the frame; you write co_await / co_return)

CV wait on a thread     ↔  await_ready / await_suspend / await_resume
                            (wait without necessarily blocking that thread —
                             see simple_awaitable.h)

Demos parallel futures' main scenarios: fulfill value, exception, async-style
delay (awaitable), and composition (nested task ≈ chaining work).
*/
#pragma endregion //MINE
