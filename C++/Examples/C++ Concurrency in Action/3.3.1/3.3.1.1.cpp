#if 1 // Problematic double-checked locking
// What can happen
// Thread 1 checks resource_ptr(❶), finds it nullptr, enters the lock, and begins initializing the resource.
// Before Thread 1 finishes initialization, Thread 2 also checks resource_ptr(❶) without locking, finds it still nullptr, and then waits for the mutex.
// If Thread 1 finishes initialization(❸) and releases the lock before Thread 2 enters its locked section, Thread 2 finds resource_ptr non - null(❷) and doesn't reinitialize.
// However, if Thread 1 has only assigned the pointer but the underlying object construction isn't fully completed yet, Thread 2 may proceed with resource_ptr->do_something() (❹) while the object isn't fully ready.
// This results in one thread using a partially constructed resource, invoking undefined behavior and possibly causing crashes or data corruption.
#include <memory>
#include <mutex>
#include <thread>
#include "../../stdafx.h"

struct some_resource {
	void do_something() {}
};

std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;

void undefined_behaviour_with_double_checked_locking() {
	if (!resource_ptr) { // ❶ thread checks pointer without sync
		std::lock_guard<std::mutex> lk(resource_mutex);
		if (!resource_ptr) { // ❷ checks again under lock
			resource_ptr.reset(new some_resource); // ❸ initializes resource
		}
	}
	resource_ptr->do_something(); // ❹ uses resource
}

int main() {
	print_file_line();

	std::thread t1(undefined_behaviour_with_double_checked_locking);
	std::thread t2(undefined_behaviour_with_double_checked_locking);
	t1.join();
	t2.join();
}
#endif //1