#ifdef MINE

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "../../stdafx.h"

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;

void worker() {
	std::this_thread::sleep_for(std::chrono::seconds(2));  // Work takes 2 seconds
	data_ready = true;
	cv.notify_one();
}

void example1() { // Example 1: wait_for - duration-based timeout (3 seconds)
	std::jthread t(worker);
	std::unique_lock lock(mtx);

	std::cout << "Waiting with wait_for(3 seconds)...\n"; 
	std::cv_status status = cv.wait_for(lock, std::chrono::seconds(3));

	if (status == std::cv_status::timeout)
		std::cout << "TIMEOUT! (but worker finished in 2 seconds - weird)\n";
	else
		std::cout << "Success! Data ready.\n";
}

void example2() { // Example 2: wait_until - absolute timeout
	std::unique_lock lock(mtx);

	data_ready = false; 
	std::jthread t2(worker);
	std::cout << "\nWaiting with wait_until(now + 1 second)...\n";

	auto timeout = std::chrono::steady_clock::now() + std::chrono::seconds(1);
	std::cv_status status = cv.wait_until(lock, timeout);

	if (status == std::cv_status::timeout)
		std::cout << "TIMEOUT! Worker needs 2 seconds, we waited 1 second.\n";
	else
		std::cout << "Success!\n";
}

void example3() { // Example 3: wait_for with predicate (best practice - automatically handles spurious wakeups)
	std::unique_lock lock(mtx);

	data_ready = false; 
	std::jthread t3(worker);
	std::cout << "\nWaiting with wait_for + predicate (3 seconds)...\n";

	bool done = cv.wait_for(lock, std::chrono::seconds(3), []() { return data_ready; });

	std::cout << (done ? "Success! Predicate true." : "TIMEOUT!") << "\n";

}

int main() {
	print_file_line();

	example1();
	example2();
	example3();

	return 0;
}
#endif //MINE
