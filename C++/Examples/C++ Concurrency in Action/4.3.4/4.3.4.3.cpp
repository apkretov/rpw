#ifdef MINE

// Table 4.1 Row 3: Timed Mutexes (Exclusive Lock Try Functions)
//	 Functions Covered: try_lock_for( duration ), try_lock_until( time_point )   
//	 Return Values: bool (true if acquired, false otherwise)

#include <print>
#include <thread>
#include <mutex>
#include <chrono>
#include "../../stdafx.h"

std::timed_mutex t_mtx;

void simulate_lock_holder() {
	t_mtx.lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	t_mtx.unlock();
}

int main() {
	print_file_line();

	std::print("--- Table 4.1 Row 3: Timed Mutex Try Locks ---\n");

	std::jthread holder(simulate_lock_holder); // Launch a thread to hold the lock so our tries fail initially
	std::this_thread::sleep_for(std::chrono::milliseconds(50)); // let holder grab it

	bool success1 = t_mtx.try_lock_for(std::chrono::milliseconds(100)); // 1. try_lock_for
	std::print("try_lock_for result (expected false): {}\n", success1);

	auto target_time = std::chrono::system_clock::now() + std::chrono::milliseconds(500); // 2. try_lock_until
	bool success2 = t_mtx.try_lock_until(target_time);
	std::print("try_lock_until result (expected true after holder releases): {}\n", success2);

	if (success2) 
		t_mtx.unlock();

	return 0;
}
#endif //MINE