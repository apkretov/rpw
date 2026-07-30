#ifndef MINE

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "../../stdafx.h"

std::mutex mtx;
std::condition_variable cv;
bool task_complete = false;
int result = 0;

void long_running_task() {
	std::cout << "Worker: Starting long task (5 seconds)...\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));  // Simulate work
	result = 42;
	task_complete = true;
	std::cout << "Worker: Task complete!\n";
	cv.notify_one();
}

int main() {
	print_file_line();

	std::jthread worker(long_running_task);
	std::unique_lock lock(mtx);

	std::cout << "Main: Do responsive work while waiting...\n";

	while (!task_complete) { // Wait with 1-second timeout intervals instead of busy-waiting
		cv.wait_for(lock, std::chrono::seconds(1)); // Main thread stays responsive - waits 1 second without blocking indefinitely
		std::cout << "Main: Still responsive... (checking again)\n"; // Can do responsive work here (update UI, check input, show progress)
	}

	std::cout << "Main: Task done! Result = " << result << "\n";
	return 0;
}
#endif //MINE
