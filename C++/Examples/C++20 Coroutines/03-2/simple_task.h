#pragma region MINE
#pragma once

// Teaching mapping (futures 4.4.1.2 ↔ coroutines):
//   simple_promise          ↔  promise_type  (compiler-facing producer API)
//   simple_future           ↔  simple_task   (caller-facing consumer / return object)
//   promise::get_future     ↔  promise_type::get_return_object
//   promise::set_value      ↔  promise_type::return_value / return_void
//   promise::set_exception  ↔  promise_type::unhandled_exception
//   future::get / wait      ↔  simple_task::get / wait  (sync teaching path)
//   (no direct futures twin) ↔  initial_suspend / final_suspend (start/end control)

#include "simple_coro_state.h"
#include <coroutine>
#include <exception>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class simple_task {
public:
	struct promise_type {
		std::shared_ptr<simple_coro_state<T>> state = std::make_shared<simple_coro_state<T>>();

		simple_task get_return_object() { // ≈ promise::get_future()
			return simple_task{std::coroutine_handle<promise_type>::from_promise(*this), state};
		}

		// Start immediately (like launching work that fulfills a future), not lazy.
		std::suspend_never initial_suspend() noexcept { return {}; }

		// Stay suspended at the end so the frame lives until simple_task destroys the handle.
		auto final_suspend() noexcept {
			struct awaiter {
				bool await_ready() const noexcept { return false; }
				void await_suspend(std::coroutine_handle<>) const noexcept {}
				void await_resume() const noexcept {}
			};
			return awaiter{};
		}

		void return_value(const T& v) { state->set_value(v); } // ≈ set_value
		void return_value(T&& v) { state->set_value(std::move(v)); }

		void unhandled_exception() { // ≈ set_exception
			state->set_exception(std::current_exception());
		}
	};

	simple_task() = default;
	simple_task(const simple_task&) = delete;
	simple_task& operator=(const simple_task&) = delete;

	simple_task(simple_task&& other) noexcept
		: handle(std::exchange(other.handle, {})), state(std::move(other.state)) {}

	simple_task& operator=(simple_task&& other) noexcept {
		if (this != &other) {
			destroy();
			handle = std::exchange(other.handle, {});
			state = std::move(other.state);
		}
		return *this;
	}

	~simple_task() { destroy(); }

	bool valid() const noexcept { return static_cast<bool>(state); }

	bool ready() const {
		if (!state)
			throw std::runtime_error("no state");
		return state->is_ready();
	}

	void wait() const { // ≈ future::wait — blocks the *thread* on a CV
		if (!state)
			throw std::runtime_error("no state");
		state->wait();
	}

	T get() { // ≈ future::get — wait first (frame must stay alive), then consume
		if (!state)
			throw std::runtime_error("no state");
		auto tmp = state;
		state.reset();
		T result = tmp->get(); // blocks here while handle still owns the frame
		destroy();
		return result;
	}

	// Awaitable protocol: co_await parks the *coroutine*, not the OS thread (vs get/wait).
	bool await_ready() const {
		if (!state)
			throw std::runtime_error("no state");
		return state->is_ready();
	}

	bool await_suspend(std::coroutine_handle<> continuation) const {
		// false → already ready between await_ready and here; do not suspend.
		return state->set_continuation(continuation);
	}

	T await_resume() {
		if (!state)
			throw std::runtime_error("no state");
		auto tmp = state;
		state.reset();
		T result = tmp->get();
		destroy();
		return result;
	}

private:
	explicit simple_task(std::coroutine_handle<promise_type> h,
		std::shared_ptr<simple_coro_state<T>> s)
		: handle(h), state(std::move(s)) {}

	void destroy() {
		if (handle) {
			handle.destroy();
			handle = {};
		}
	}

	std::coroutine_handle<promise_type> handle{};
	std::shared_ptr<simple_coro_state<T>> state;
};

template <>
class simple_task<void> {
public:
	struct promise_type {
		std::shared_ptr<simple_coro_state<void>> state = std::make_shared<simple_coro_state<void>>();

		simple_task get_return_object() {
			return simple_task{std::coroutine_handle<promise_type>::from_promise(*this), state};
		}

		std::suspend_never initial_suspend() noexcept { return {}; }

		auto final_suspend() noexcept {
			struct awaiter {
				bool await_ready() const noexcept { return false; }
				void await_suspend(std::coroutine_handle<>) const noexcept {}
				void await_resume() const noexcept {}
			};
			return awaiter{};
		}

		void return_void() { state->set_value(); } // ≈ set_value() for void
		void unhandled_exception() { state->set_exception(std::current_exception()); }
	};

	simple_task() = default;
	simple_task(const simple_task&) = delete;
	simple_task& operator=(const simple_task&) = delete;

	simple_task(simple_task&& other) noexcept
		: handle(std::exchange(other.handle, {})), state(std::move(other.state)) {}

	simple_task& operator=(simple_task&& other) noexcept {
		if (this != &other) {
			destroy();
			handle = std::exchange(other.handle, {});
			state = std::move(other.state);
		}
		return *this;
	}

	~simple_task() { destroy(); }

	bool valid() const noexcept { return static_cast<bool>(state); }

	bool ready() const {
		if (!state)
			throw std::runtime_error("no state");
		return state->is_ready();
	}

	void wait() const {
		if (!state)
			throw std::runtime_error("no state");
		state->wait();
	}

	void get() {
		if (!state)
			throw std::runtime_error("no state");
		auto tmp = state;
		state.reset();
		tmp->get();
		destroy();
	}

	bool await_ready() const {
		if (!state)
			throw std::runtime_error("no state");
		return state->is_ready();
	}

	bool await_suspend(std::coroutine_handle<> continuation) const {
		return state->set_continuation(continuation);
	}

	void await_resume() {
		if (!state)
			throw std::runtime_error("no state");
		auto tmp = state;
		state.reset();
		tmp->get();
		destroy();
	}

private:
	explicit simple_task(std::coroutine_handle<promise_type> h,
		std::shared_ptr<simple_coro_state<void>> s)
		: handle(h), state(std::move(s)) {}

	void destroy() {
		if (handle) {
			handle.destroy();
			handle = {};
		}
	}

	std::coroutine_handle<promise_type> handle{};
	std::shared_ptr<simple_coro_state<void>> state;
};
#pragma endregion //MINE
