#include <coroutine>
#include "../../stdafx.h"

struct SimpleCoroutine {
	struct promise_type {
		SimpleCoroutine get_return_object() { return {}; }
		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
};

SimpleCoroutine my_first_coroutine() {
	co_return;  // This makes it a coroutine
}

int main() {
	print_file_line();
	my_first_coroutine();
	return 0;
}