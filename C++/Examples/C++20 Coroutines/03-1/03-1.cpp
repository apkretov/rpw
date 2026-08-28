#include <coroutine>
#include <iostream>
#include <thread>
#include "../../stdafx.h"

struct ReturnObject {
	struct promise_type {
		ReturnObject get_return_object() { 
			std::cout << std::this_thread::get_id() << " 111 get_return_object()" << std::endl; //MINE
			return {}; 
		}

		std::suspend_never initial_suspend() { 
			std::cout << std::this_thread::get_id() << " 222 initial_suspend()" << std::endl; //MINE
			return {}; 
		}

		std::suspend_never final_suspend() noexcept { 
			std::cout << std::this_thread::get_id() << " 555 final_suspend()" << std::endl; //MINE
			return {}; 
		}

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
	// MINE for (unsigned i = 0; i < 3; ++i) { // This calls final_suspend() and prints 555.
		std::cout << std::this_thread::get_id() << " 333 counter: " << i << std::endl;
		co_await awaiter;
	}
}

int main() {
	print_file_line();

	std::coroutine_handle<> h;
	counter(&h);

	for (int i = 0; i < 3; ++i) {
		std::cout << std::this_thread::get_id() << " 444 main: resuming" << std::endl;
		h();
	}

	h.destroy(); // Comment this out to call final_suspend() to print 555.
}