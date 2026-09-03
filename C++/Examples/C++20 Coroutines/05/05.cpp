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
			if (handle) handle.destroy();
			handle = other.handle;
			other.handle = nullptr;
		}
		return *this;
	}

	bool next() {
		if (!handle || handle.done())
			return false;
		handle.resume();
		return !handle.done();
	}

	int value() const {
		return handle.promise().current_value;
	}
};

Generator count_to(int n) {
	for (int i = 1; i <= n; ++i) {
		co_yield i;
	}
}

int main() {
	print_file_line();

	auto gen = count_to(5);

	while (gen.next()) {
		std::cout << gen.value() << std::endl;
	}
}