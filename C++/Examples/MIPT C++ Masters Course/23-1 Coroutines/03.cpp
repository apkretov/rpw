#if 1

#include "../../stdafx.h"
#include "vld.h"
import std;

#pragma region MINE
struct resumable {
	struct promise_type {
		resumable get_return_object() { return {std::coroutine_handle<promise_type>::from_promise(*this)}; }
		std::suspend_always initial_suspend() { return {}; }

		void return_void() {}
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { std::terminate(); }
	};

	std::coroutine_handle<promise_type> handle;

	resumable(std::coroutine_handle<promise_type> h) : handle(h) {}
	resumable(const resumable&) = delete;
	resumable& operator=(const resumable&) = delete;
	resumable(resumable&& other) noexcept : handle(other.handle) { other.handle = nullptr; }

	resumable& operator=(resumable&& other) noexcept {
		if (&other != this) {
			if (handle)
				handle.destroy();
			handle = other.handle;
			other.handle = nullptr;
		}
		return *this;
	}

	~resumable() noexcept {
		if (handle)
			handle.destroy();
	}

	void resume() const {
		if (!handle || handle.done())
			return;
		handle.resume();
	}
};
#pragma endregion //MINE

resumable foo() {
	std::cout << "Hello, " << std::endl;
	co_await std::suspend_always{};
	std::cout << "World!" << std::endl;
}

int main() {
	print_file_line();

	auto t = foo();
	t.resume();
	t.resume();

	return 0;
}
#endif // 1
