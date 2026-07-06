#ifndef MINE

// Table 4.1 Row 7: Futures (std::future / std::shared_future)
//   Functions Covered: wait_for(duration), wait_until(time_point)   
//   Return Values: std::future_status (timeout, ready, or deferred)

#include <print>
#include <future>
#include <chrono>
#include <thread>
#include "../../stdafx.h"

int slow_task() {
	std::this_thread::sleep_for(std::chrono::milliseconds(400));
	return 100;
}

int main() {
	print_file_line();

	std::print("--- Table 4.1 Row 7: Future Status Timing Examples ---\n");

	std::future<int> fut = std::async(std::launch::async, slow_task); // Launch an async task

	std::future_status status1 = fut.wait_for(std::chrono::milliseconds(100)); // 1. Test wait_for (using a small duration to trigger a timeout status)
	if (status1 == std::future_status::timeout)
		std::print("wait_for result: std::future_status::timeout\n");

	auto target_time = std::chrono::system_clock::now() + std::chrono::milliseconds(500); // 2. Test wait_until (giving it enough time to become ready)
	std::future_status status2 = fut.wait_until(target_time);

	if (status2 == std::future_status::ready) {
		std::print("wait_until result: std::future_status::ready\n");
		std::print("Task Result: {}\n", fut.get());
	}

	return 0;
}
#endif //MINE
