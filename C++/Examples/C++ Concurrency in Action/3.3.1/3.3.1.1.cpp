#if 0 // Problematic double-checked locking
/* What can happen
Thread 1 checks resource_ptr(❶), finds it nullptr, enters the lock, and begins initializing the resource.
Before Thread 1 finishes initialization, Thread 2 also checks resource_ptr(❶) without locking, finds it still nullptr, and then waits for the mutex.
If Thread 1 finishes initialization(❸) and releases the lock before Thread 2 enters its locked section, Thread 2 finds resource_ptr non - null(❷) and doesn't reinitialize.
However, if Thread 1 has only assigned the pointer but the underlying object construction isn't fully completed yet, Thread 2 may proceed with resource_ptr->do_something() (❹) while the object isn't fully ready. 
This can happen because modern CPUs and compilers reorder operations for performance. So, without synchronization no ordering is guaranteed between threads. At line ❶, Thread 2 reads resource_ptr without any synchronization.
This results in one thread using a partially constructed resource, invoking undefined behavior and possibly causing crashes or data corruption. 
*/
#include <memory>
#include <mutex>
#include <print>
#include <thread>
#include "../../stdafx.h"

struct some_resource {
	void do_something() {}
};

std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void undefined_behaviour_with_double_checked_locking() {
	std::print("111 Thread {} is checking resource_ptr\n", std::this_thread::get_id()); //MINE
	if (!resource_ptr) { // ❶ thread checks pointer without sync
		std::print("222 Thread {} is trying to acquire lock\n", std::this_thread::get_id()); //MINE
		std::lock_guard lk(resource_mutex);
		std::print("333 Thread {} has acquired lock\n", std::this_thread::get_id()); //MINE
		if (!resource_ptr) { // ❷ checks again under lock
			std::print("444 Thread {} is initializing resource\n", std::this_thread::get_id()); //MINE
			resource_ptr.reset(new some_resource); // ❸ initializes resource
		}
	}
	std::print("555 Thread {} is using resource\n", std::this_thread::get_id()); //MINE
	resource_ptr->do_something(); // ❹ uses resource
}

int main() {
	print_file_line();

	std::jthread t1(undefined_behaviour_with_double_checked_locking);
	std::jthread t2(undefined_behaviour_with_double_checked_locking);
}
#endif //1
