#if 1

#include <coroutine>
#include <optional>
#include "../../stdafx.h"

struct ComputeResult2 {
	struct promise_type {
		int result = 0;

		ComputeResult2 get_return_object() {
			return ComputeResult2{
				std::coroutine_handle<promise_type>::from_promise(*this)
			};
		}
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void return_void() {}  // Required because we fall off the end
		void unhandled_exception() {}
	};

	std::coroutine_handle<promise_type> handle;

	ComputeResult2(std::coroutine_handle<promise_type> h) : handle(h) {}

	~ComputeResult2() {
		if (handle)
			handle.destroy();
	}

	ComputeResult2(ComputeResult2&& other) noexcept : handle(other.handle) { other.handle = nullptr; }

	void run() {
		//std::println("005 run: while"); //MINE
		while (!handle.done()) {
			//std::println("006 run: handle.resume()"); //MINE
			handle.resume();
		}
	}

	std::optional<int> get_result() const { return handle.promise().result; }
};

#pragma region MINE
struct GetPromiseAwaiter { // Awaiter that hands the coroutine body a reference to its own promise's result. // await_suspend returns false, so the coroutine never actually suspends here.
	ComputeResult2::promise_type* promise = nullptr;
	bool await_ready() const noexcept { return false; }

	bool await_suspend(std::coroutine_handle<ComputeResult2::promise_type> h) noexcept {
		promise = &h.promise();
		return false;
	}

	int& await_resume() const noexcept { return promise->result; }
};
#pragma endregion //MINE

ComputeResult2 compute_sum2(int n) {
	auto& result = co_await GetPromiseAwaiter{};
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		sum += i;
		co_await std::suspend_always{};
	}
	result = sum;
	// Falls off the end - calls promise.return_void()
}

int main() {
	print_file_line();

	//std::println("001 main: compute_sum(5)"); //MINE
	auto computation = compute_sum2(5);
	//std::println("004 main: computation.run()"); //MINE
	computation.run();

	if (auto result = computation.get_result()) {
		std::cout << "Result: " << *result << std::endl;
	}
}
#endif // 1
