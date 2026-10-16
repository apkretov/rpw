#include <coroutine>
#include <exception>
#include "../../stdafx.h"

#pragma region MINE
struct Generator {
	struct promise_type {
		int current_value;

		Generator get_return_object() { return {std::coroutine_handle<promise_type>::from_promise(*this)}; }
		std::suspend_always initial_suspend() { return {}; }

		std::suspend_always yield_value(int value) {
			current_value = value;
			return {};
		}

		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { std::terminate(); }
	};

	std::coroutine_handle<promise_type> handle;

	Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
};
#pragma endregion //MINE

static Generator num(int n) {
	int i = 0;
	while (i < n) {
		++i;
		co_yield i;
	}
}

int main() {
	print_file_line();



	return 0;
}