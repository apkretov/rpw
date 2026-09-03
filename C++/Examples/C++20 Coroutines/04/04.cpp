#include <coroutine>
#include <iostream>
#include "../../stdafx.h"
#include "vld.h" //MINE

struct TracePromise {
	struct promise_type {
		promise_type() { std::cout << "promise constructed" << std::endl; }
		~promise_type() { std::cout << "promise destroyed" << std::endl; }

		TracePromise get_return_object() {
			std::cout << "get_return_object called" << std::endl;
			return {};
		}

		std::suspend_never initial_suspend() {
			std::cout << "initial_suspend called" << std::endl;
			return {};
		}

		std::suspend_always final_suspend() noexcept {
			std::cout << "final_suspend called" << std::endl;
			return {};
		}

		void return_void() { std::cout << "return_void called" << std::endl; }
		void unhandled_exception() { std::cout << "unhandled_exception called" << std::endl; }
	};

	std::coroutine_handle<promise_type> handle;
};

TracePromise trace_coroutine() {
	std::cout << "coroutine body begins" << std::endl;
	co_return;
}

int main() {
	print_file_line();

	std::cout << "calling coroutine" << std::endl;
	auto result = trace_coroutine();
	std::cout << "coroutine returned" << std::endl;
}