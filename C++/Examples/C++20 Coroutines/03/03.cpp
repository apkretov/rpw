#include <coroutine>
#include <iostream>
#include "../../stdafx.h"

struct ReturnObject {
	struct promise_type {
		ReturnObject get_return_object() { return {}; }
		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
};

struct Awaiter {
	std::coroutine_handle<>* handle_out;

	bool await_ready() { return false; }
	void await_suspend(std::coroutine_handle<> h) { *handle_out = h; }
	void await_resume() {}
};

ReturnObject counter(std::coroutine_handle<>* handle) {
	Awaiter awaiter{handle};

	for (unsigned i = 0; ; ++i) {
		std::cout << "counter: " << i << std::endl;
		co_await awaiter;
	}
}

int main() {
	print_file_line();

	std::coroutine_handle<> h;
	counter(&h);

	for (int i = 0; i < 3; ++i) {
		std::cout << "main: resuming" << std::endl;
		h();
	}

	h.destroy();
}