#pragma region MINE
#pragma once

// Teaching analogue of shared_state.h from the futures model (4.4.1.2).
//
// Futures:  shared_state holds value/exception + ready + mutex/cv.
// Coroutines: the *real* compiler-generated frame also holds locals and a
// resume program-counter. This struct is only the educational slice that
// maps to "shared result + how waiters/continuations wake up".

#include <condition_variable>
#include <coroutine>
#include <exception>
#include <mutex>
#include <utility>

template <typename T>
class simple_coro_state {
public:
	void set_value(const T& v) { // ≈ shared_state::set_value / promise::set_value
		{
			std::scoped_lock lock(m);
			value = v;
			ready = true;
		}
		cv.notify_all();
		resume_continuation();
	}

	void set_value(T&& v) {
		{
			std::scoped_lock lock(m);
			value = std::move(v);
			ready = true;
		}
		cv.notify_all();
		resume_continuation();
	}

	void set_exception(std::exception_ptr e) { // ≈ shared_state::set_exception
		{
			std::scoped_lock lock(m);
			exc = e;
			has_exception = true;
			ready = true;
		}
		cv.notify_all();
		resume_continuation();
	}

	void wait() { // Blocking wait — same idea as future::wait / CV wait.
		std::unique_lock lock(m);
		cv.wait(lock, [this] { return ready; });
	}

	T get() { // Blocking get — same idea as future::get.
		wait();
		if (has_exception)
			std::rethrow_exception(exc);
		return value;
	}

	bool is_ready() const {
		std::scoped_lock lock(m);
		return ready;
	}

	// For co_await of a task: store who to resume instead of parking a thread on the CV.
	// Returns true if the awaiter should stay suspended; false if already ready (resume now).
	bool set_continuation(std::coroutine_handle<> h) {
		std::scoped_lock lock(m);
		if (ready)
			return false;
		continuation = h;
		return true;
	}

private:
	void resume_continuation() {
		std::coroutine_handle<> h;
		{
			std::scoped_lock lock(m);
			h = continuation;
			continuation = {};
		}
		if (h)
			h.resume();
	}

	T value{};
	bool ready = false;
	bool has_exception = false;
	std::exception_ptr exc;
	std::coroutine_handle<> continuation{}; // non-blocking wake path for awaiters

	mutable std::mutex m;
	std::condition_variable cv;
};

template <>
class simple_coro_state<void> {
public:
	void set_value() {
		{
			std::scoped_lock lock(m);
			ready = true;
		}
		cv.notify_all();
		resume_continuation();
	}

	void set_exception(std::exception_ptr e) {
		{
			std::scoped_lock lock(m);
			exc = e;
			has_exception = true;
			ready = true;
		}
		cv.notify_all();
		resume_continuation();
	}

	void wait() {
		std::unique_lock lock(m);
		cv.wait(lock, [this] { return ready; });
	}

	void get() {
		wait();
		if (has_exception)
			std::rethrow_exception(exc);
	}

	bool is_ready() const {
		std::scoped_lock lock(m);
		return ready;
	}

	bool set_continuation(std::coroutine_handle<> h) {
		std::scoped_lock lock(m);
		if (ready)
			return false;
		continuation = h;
		return true;
	}

private:
	void resume_continuation() {
		std::coroutine_handle<> h;
		{
			std::scoped_lock lock(m);
			h = continuation;
			continuation = {};
		}
		if (h)
			h.resume();
	}

	bool ready = false;
	bool has_exception = false;
	std::exception_ptr exc;
	std::coroutine_handle<> continuation{};

	mutable std::mutex m;
	std::condition_variable cv;
};
#pragma endregion //MINE
