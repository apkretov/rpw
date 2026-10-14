#if 1

#include <coroutine>
#include <iostream>
//OFF #include "vld.h"
#include "../../stdafx.h"

struct Task {
	struct promise_type {
		Task get_return_object() {
			std::cout << "Creating return object" << std::endl;
			return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
		}
		
		std::suspend_always initial_suspend() {
			std::cout << "Initial suspend" << std::endl;
			return {};
		}
		
		std::suspend_always final_suspend() noexcept {
			std::cout << "Final suspend" << std::endl;
			return {};
		}
		
		void return_void() {}
		void unhandled_exception() {}
	};

	std::coroutine_handle<promise_type> handle;

	Task(std::coroutine_handle<promise_type> h) : handle(h) {}
	
	~Task() {
		if (handle)
			handle.destroy();
	}

	Task(Task&& other) noexcept : handle(other.handle) { other.handle = nullptr; }
	void resume() { handle.resume(); }
	bool done() const { return handle.done(); }
};

Task example_task() {
	std::cout << "Task body : part 1" << std::endl;
	co_await std::suspend_always{};
	std::cout << "Task body : part 2" << std::endl;
}

int main() {
	print_file_line();

	std::cout << "Before calling coroutine" << std::endl;

	Task task = example_task();

	std::cout << "After calling coroutine, before first resume" << std::endl;
	task.resume();

	std::cout << "After first resume, before second resume" << std::endl;
	task.resume();

	std::cout << "After second resume" << std::endl;
}
#endif // 1
