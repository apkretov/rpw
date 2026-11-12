#if 1

#include "../../stdafx.h" //MINE
import std;

#pragma region MINE
template <typename T>
struct generator {
	struct promise_type {
		T current_value;

		generator get_return_object() { return {std::coroutine_handle<promise_type>::from_promise(*this)}; }
		std::suspend_always initial_suspend() { return {}; }

		std::suspend_always yield_value(T value) {
			current_value = value;
			return {};
		}

		void return_void() {}
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() { std::terminate(); }
	};

	std::coroutine_handle<promise_type> handle;

	generator(std::coroutine_handle<promise_type> h) : handle(h) {}
	generator(const generator&) = delete;
	generator& operator=(const generator&) = delete;
	generator(generator&& other) noexcept : handle(other.handle) { other.handle = nullptr; }

	generator& operator=(generator&& other) noexcept {
		if (&other != this) {
			if (handle)
				handle.destroy();
			handle = other.handle;
			other.handle = nullptr;
		}
		return *this;
	}

	~generator() noexcept {
		if (handle)
			handle.destroy();
	}

	bool move_next() const {
		if (!handle || handle.done())
			return false;
		handle.resume();
		return !handle.done();
	}

	T current_value() const { return handle.promise().current_value; }
};
#pragma endregion //MINE

template <typename T>
generator<T> sequence(int start, int fin, int step) {
	for (int num = start; num < fin; num += step) {
		co_yield num;
	}
}

#pragma region MINE
int main() {
	print_file_line(); //MINE

	#ifndef WHILE
	auto nums = sequence<int>(5, 20, 3);
	while (nums.move_next())
		std::cout << AS_KV(nums.current_value()) << '\n';
	#else //RANGE_BASED_ERR
	for (const auto& it : sequence<int>(5, 20, 3))
		;
	#endif //RANGE_BASED

	return 0;
}
#pragma endregion //MINE
#endif //1