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

generator<int> natural_nums() {
	int num = 0;
	int num_2 = 0; //MINE
	for (;;) {
		std::println("num = {}\tnum_2 = {}", num, num_2++); //MINE
		co_yield num;
		num += 1;
	}
}

int main() {
	print_file_line(); //MINE

	auto nums = natural_nums();
	nums.move_next();
	auto y = nums.current_value(); // y = 0
	std::cout << AS_KV(y) << '\n'; //MINE
	nums.move_next();
	auto z = nums.current_value(); // z = 1
	std::cout << AS_KV(z) << '\n'; //MINE

	return 0;
}
#endif //1