#if 0

#include <coroutine>
#include <iostream>
#include <optional>
#include <print>
#include "../../stdafx.h"

struct ComputeResult {
	struct promise_type {
		std::optional<int> result;

		ComputeResult get_return_object() {
			std::println("002 get_return_object()"); //MINE
			return ComputeResult{std::coroutine_handle<promise_type>::from_promise(*this)};
		}

		std::suspend_always initial_suspend() {
			std::println("003 initial_suspend()"); //MINE
			return {};
		}

		std::suspend_always final_suspend() noexcept {
			std::println("011 final_suspend"); //MINE
			return {};
		}

		void return_value(int value) {
			std::println("010 return_value: value = {}", value); //MINE
			result = value;
		}

		void unhandled_exception() { result = std::nullopt; }
	};

	std::coroutine_handle<promise_type> handle;
	ComputeResult(std::coroutine_handle<promise_type> h) : handle(h) {}

	~ComputeResult() {
		if (handle)
			handle.destroy();
	}

	ComputeResult(ComputeResult&& other) noexcept : handle(other.handle) { other.handle = nullptr; }

	void run() {
		std::println("005 run: while"); //MINE
		while (!handle.done()) {
			std::println("006 run: handle.resume()"); //MINE
			handle.resume();
		}
	}

	std::optional<int> get_result() const { return handle.promise().result; }
};

ComputeResult compute_sum(int n) {
	std::println("007 compute_sum"); //MINE
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += i;
		std::println("008 compute_sum: co_await i = {}, sum = {}", i, sum); //MINE
		co_await std::suspend_always{};  // yield control periodically
	}
	std::println("009 compute_sum: co_return sum = {}", sum); //MINE
	co_return sum;
}

int main() {
	print_file_line();

	std::println("001 main: compute_sum(5)"); //MINE
	auto computation = compute_sum(5);
	std::println("004 main: computation.run()"); //MINE
	computation.run();

	if (auto result = computation.get_result()) {
		std::cout << "Result: " << *result << std::endl;
	}
}
#endif // 1
