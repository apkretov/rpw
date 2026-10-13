#if 1

#include <coroutine>
#include <iostream>
#include "../../stdafx.h"

struct Generator {
	struct promise_type {
		int current_value;

		Generator get_return_object() { return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }

		std::suspend_always yield_value(int value) {
			current_value = value;
			return {};
		}

		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};

	std::coroutine_handle<promise_type> handle;

	Generator(std::coroutine_handle<promise_type> h) : handle(h) {}

	~Generator() {
		if (handle)
			handle.destroy();
	}

	Generator(const Generator&) = delete; // Disable copying
	Generator& operator=(const Generator&) = delete;
	Generator(Generator&& other) noexcept : handle(other.handle) { other.handle = nullptr; } // Enable moving

	Generator& operator=(Generator&& other) noexcept {
		if (this != &other) {
			if (handle)
				handle.destroy();
			handle = other.handle;
			other.handle = nullptr;
		}
		return *this;
	}

	bool next() {
		if (!handle || handle.done()) // See the note about done() below.
			return false;
		handle.resume();
		return !handle.done();
	}

	int value() const { return handle.promise().current_value; }
};

Generator fibonacci() {
	int a = 0, b = 1;
	while (true) {
		co_yield a;
		int next = a + b;
		a = b;
		b = next;
	}
}

int main() {
	print_file_line();

	auto fib = fibonacci();

	for (int i = 0; i < 10 && fib.next(); ++i) {
		std::cout << fib.value() << " ";
	}
	std::cout << std::endl;
}
#endif // 1
