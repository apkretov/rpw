#ifdef MINE

// Table 4.1 Row 4: Shared Timed Mutex (Shared Lock Try Functions)
//   Functions Covered: try_lock_shared_for( duration ), try_lock_shared_until( time_point )   
//   Return Values: bool (true if acquired, false otherwise)

#include <thread>
#include <shared_mutex>
#include <chrono>
#include <print>
#include "../../stdafx.h"

std::shared_timed_mutex st_mtx;

void hold_exclusive_lock() {
	st_mtx.lock(); // Exclusive write lock blocks shared read locks
	std::this_thread::sleep_for(std::chrono::milliseconds(400));
	st_mtx.unlock();
}

int main() {
	print_file_line();

	std::print("--- Table 4.1 Row 4: Shared Timed Mutex Shared Try Locks ---\n");

	std::jthread holder(hold_exclusive_lock);
	std::this_thread::sleep_for(std::chrono::milliseconds(50)); // let holder grab it

	bool shared_success1 = st_mtx.try_lock_shared_for(std::chrono::milliseconds(100)); // 1. try_lock_shared_for
	std::print("try_lock_shared_for result (expected false): {}\n", shared_success1);

	auto target_time = std::chrono::system_clock::now() + std::chrono::milliseconds(500); // 2. try_lock_shared_until
	bool shared_success2 = st_mtx.try_lock_shared_until(target_time);
	std::print("try_lock_shared_until result (expected true): {}\n", shared_success2);

	if (shared_success2)
		st_mtx.unlock_shared();

	return 0;
}
#endif //MINE