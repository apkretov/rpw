#pragma once

#pragma region MINE

#include <coroutine>
#include <condition_variable>
#include <exception>
#include <mutex>
#include <type_traits>
#include <utility>

template<typename T = void>
class task { // Minimal coroutine return type for this teaching example. handle_request returns task<void>; main waits with ready() / get().
	static_assert(std::is_void_v<T>, "This example only implements task<void>");
public:
	struct promise_type {
		std::mutex mutex;
		std::condition_variable cv;
		bool done = false;
		std::exception_ptr exception;

		task get_return_object() { return task{std::coroutine_handle<promise_type>::from_promise(*this)}; }
		std::suspend_never initial_suspend() noexcept { return {}; }

		auto final_suspend() noexcept {
			struct awaiter {
				promise_type& p;
				bool await_ready() const noexcept { return false; }
				void await_suspend(std::coroutine_handle<>) const noexcept {
					{
						std::scoped_lock lock(p.mutex);
						p.done = true;
					}
					p.cv.notify_one();
				}
				void await_resume() const noexcept {}
			};
			return awaiter{*this};
		}

		void return_void() {}
		void unhandled_exception() { exception = std::current_exception(); }
	};

	task(const task&) = delete;
	task& operator=(const task&) = delete;
	task(task&& other) noexcept : handle(std::exchange(other.handle, {})) {}

	task& operator=(task&& other) noexcept {
		if (this != &other) {
			if (handle)
				handle.destroy();
			handle = std::exchange(other.handle, {});
		}
		return *this;
	}

	~task() {
		if (handle)
			handle.destroy();
	}

	bool ready() const {
		std::scoped_lock lock(handle.promise().mutex);
		return handle.promise().done;
	}

	void get() {
		std::unique_lock lock(handle.promise().mutex);
		handle.promise().cv.wait(lock, [&] { return handle.promise().done; });
		if (handle.promise().exception)
			std::rethrow_exception(handle.promise().exception);
	}
private:
	explicit task(std::coroutine_handle<promise_type> h) : handle(h) {}
	std::coroutine_handle<promise_type> handle;
};
#pragma endregion //MINE
