#if 1

#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include "../../stdafx.h"

#pragma region MINE
int some_task() {
#ifdef TIMED_OUT
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
#else
	std::this_thread::sleep_for(std::chrono::milliseconds(15));
#endif
	return 42;
}

void do_something_with(int result) { std::cout << "Task completed with result: " << result << std::endl; }
#pragma endregion //MINE

int main() {
	print_file_line();

	std::future<int> f = std::async(some_task);
	if (f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)
		do_something_with(f.get());
	else //MINE
		std::cout << "Task timed out." << std::endl; //MINE

	return 0;
}
#endif //1
