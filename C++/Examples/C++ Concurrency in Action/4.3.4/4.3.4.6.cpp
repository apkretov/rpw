#ifdef MINE

// Table 4.1 Row 6: std::shared_lock Wrapper Timing
//    Functions Covered: Constructor wrappers (shared_lock(lockable, duration), shared_lock(lockable, time_point)) 
//		 and member functions (try_lock_for(duration), try_lock_until(time_point)).  
//    Return Values: Constructors return N/A (check via owns_lock()) ; member functions return bool.

#include <shared_mutex>
#include <chrono>
#include <print>
#include "../../stdafx.h"

std::shared_timed_mutex st_mtx;

int main() {
	print_file_line();

	std::print("--- Table 4.1 Row 6: std::shared_lock Timed Examples ---\n");

	st_mtx.lock(); // Lock exclusively to block shared attempts

	{ // 1. Constructor with duration
		std::shared_lock<std::shared_timed_mutex> s_lock(st_mtx, std::chrono::milliseconds(100));
		std::print("Constructor duration owns_lock(): {}\n", s_lock.owns_lock());
	}

	{ // 2. Constructor with time_point
		auto timeout = std::chrono::system_clock::now() + std::chrono::milliseconds(100);
		std::shared_lock<std::shared_timed_mutex> s_lock(st_mtx, timeout);
		std::print("Constructor time_point owns_lock(): {}\n", s_lock.owns_lock());
	}

	std::shared_lock<std::shared_timed_mutex> deferred_s_lock(st_mtx, std::defer_lock); // 3. Member functions using a deferred shared_lock

	bool member_success1 = deferred_s_lock.try_lock_for(std::chrono::milliseconds(100));
	std::print("Member try_lock_for result: {}\n", member_success1);

	st_mtx.unlock(); // Free the exclusive lock

	auto timeout2 = std::chrono::system_clock::now() + std::chrono::milliseconds(100);
	bool member_success2 = deferred_s_lock.try_lock_until(timeout2);
	std::print("Member try_lock_until result (after unlock): {}\n", member_success2);

	return 0;
}

#endif //MINE
