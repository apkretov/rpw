#ifdef MINE

//  Row 2: std::condition_variable Wait Functions
//	 Functions Covered: wait_for( lock, duration ), wait_until( lock , time_point ) (returning std::cv_status), 
//	 and the predicate-based overloads wait_for( lock, duration, predicate ), wait_until( lock, time_point, predicate ) (returning bool).

#include <mutex>
#include <condition_variable>
#include <chrono>
#include <print>
#include "../../stdafx.h"

std::mutex cv_mtx;
std::condition_variable cv;
bool data_ready = false;

int main() {
	print_file_line();

	std::print("--- Table 4.1 Row 2: std::condition_variable Examples ---\n");

	{ // --- Part A: Standard timeout waits (Returns std::cv_status) ---
		std::unique_lock lock(cv_mtx);

		std::cv_status status1 = cv.wait_for(lock, std::chrono::milliseconds(200)); // 1. wait_for
		if (status1 == std::cv_status::timeout)
			std::print("wait_for timed out as expected.\n");

		auto timeout_time = std::chrono::system_clock::now() + std::chrono::milliseconds(200); // 2. wait_until
		std::cv_status status2 = cv.wait_until(lock, timeout_time);
		if (status2 == std::cv_status::timeout) 
			std::print("wait_until timed out as expected.\n");
	}

	{ // --- Part B: Predicate timeout waits (Returns bool) ---
		std::unique_lock lock(cv_mtx);

		bool condition_met1 = cv.wait_for(lock, std::chrono::milliseconds(200), [] { return data_ready; }); // 3. wait_for with predicate
		std::print("wait_for (predicate) returned: {}\n", condition_met1);

		auto timeout_time2 = std::chrono::system_clock::now() + std::chrono::milliseconds(200); // 4. wait_until with predicate
		bool condition_met2 = cv.wait_until(lock, timeout_time2, [] { return data_ready; });
		std::print("wait_until (predicate) returned: {}\n", condition_met2);
	}

	return 0;
}
#endif //MINE
