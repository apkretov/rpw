#pragma region MINE
#pragma once

// Awaitable protocol teaching piece.
//
// Futures model: future::wait / get park the *OS thread* on a condition_variable
// until shared_state is ready.
//
// Coroutine model: co_await parks the *coroutine* (saves locals + resume PC in the
// frame). The thread can go do other work; later someone calls handle.resume().
//
// Protocol (what co_await expands to, roughly):
//   if (!await_ready())
//       await_suspend(current_coroutine_handle);  // may schedule resume elsewhere
//   await_resume();                               // produce the co_await expression value

#include <chrono>
#include <coroutine>
#include <print>
#include <thread>
#include <utility>

using namespace std::chrono_literals;

// Sleep on a background thread, then resume the awaiting coroutine.
// Like a tiny "async timer" — not a CV wait on the caller thread.
struct resume_after {
	std::chrono::milliseconds delay;

	bool await_ready() const noexcept {
		return delay.count() <= 0; // already "done" → skip suspend
	}

	void await_suspend(std::coroutine_handle<> continuation) const {
		std::println("{}  resume_after: suspending coroutine; launching sleeper thread",
			std::this_thread::get_id());
		std::jthread([continuation, d = delay] {
			std::this_thread::sleep_for(d);
			std::println("{}  resume_after: delay done; resuming coroutine",
				std::this_thread::get_id());
			continuation.resume();
		}).detach();
	}

	void await_resume() const noexcept {
		// Nothing to return; side effect was the delay + thread hop.
	}
};

// Resume the awaiting coroutine on a fresh thread (no sleep).
struct resume_on_new_thread {
	bool await_ready() const noexcept { return false; }

	void await_suspend(std::coroutine_handle<> continuation) const {
		std::println("{}  resume_on_new_thread: handing off",
			std::this_thread::get_id());
		std::jthread([continuation] {
			std::println("{}  resume_on_new_thread: resuming here",
				std::this_thread::get_id());
			continuation.resume();
		}).detach();
	}

	void await_resume() const noexcept {}
};
#pragma endregion //MINE
