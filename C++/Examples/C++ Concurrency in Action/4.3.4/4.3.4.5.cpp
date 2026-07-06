#ifdef MINE

// Table 4.1 Row 5: std::unique_lock Wrapper Timing
//   Functions Covered: Constructor wrappers (unique_lock(lockable, duration), unique_lock(lockable, time_point)) 
//		and member functions (try_lock_for(duration), try_lock_until(time_point)).
//   Return Values: Constructors return N/A (check via owns_lock()) ; member functions return bool.

#include <mutex>
#include <chrono>
#include <print>
#include "../../stdafx.h"

std::timed_mutex t_mtx;

int main() {
	print_file_line();

	std::print("--- Table 4.1 Row 5: std::unique_lock Timed Examples ---\n");

	t_mtx.lock(); // Hold the mutex now to test timeout behavior in following lock calls

	{ // 1. Constructor with duration
		std::unique_lock<std::timed_mutex> u_lock(t_mtx, std::chrono::milliseconds(100));
		std::print("Constructor duration owns_lock(): {}\n", u_lock.owns_lock());
	}

	{ // 2. Constructor with time_point
		auto timeout = std::chrono::system_clock::now() + std::chrono::milliseconds(100);
		std::unique_lock<std::timed_mutex> u_lock(t_mtx, timeout);
		std::print("Constructor time_point owns_lock(): {}\n", u_lock.owns_lock());
	}

	std::unique_lock<std::timed_mutex> deferred_lock(t_mtx, std::defer_lock); // 3. Member functions using a deferred unique_lock

	bool member_success1 = deferred_lock.try_lock_for(std::chrono::milliseconds(100));
	std::print("Member try_lock_for result: {}\n", member_success1);

	t_mtx.unlock(); // Free it up

	auto timeout2 = std::chrono::system_clock::now() + std::chrono::milliseconds(100);
	bool member_success2 = deferred_lock.try_lock_until(timeout2);
	std::print("Member try_lock_until result (after unlock): {}\n", member_success2);

	return 0;
}
#endif //MINE