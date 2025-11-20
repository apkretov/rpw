#ifdef MINE // Problematic double-checked locking - Demonstrating use-after-invalidation
// What can happen
// Both threads check resource_ptr at ❶ and see nullptr.
// Both enter the mutex — one waits for the other.
// The first thread to lock creates the resource at ❸.
// After the first thread exits, the second thread enters the locked section at ❷, sees resource_ptr is now non-null, and continues.
// Both threads end up using resource_ptr at ❹.
// If resource_ptr's ownership or content changes between these steps (for instance, if the resource could be reset or destroyed in another context), the second thread could access an invalid or partially constructed object, leading to undefined behavior or a crash.
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <cstring>
#include "../../stdafx.h"
using namespace std;

struct some_resource {
	bool is_valid;
	
	some_resource() : is_valid(true) {
		cout << "Resource constructed.\n";
		this_thread::sleep_for(chrono::milliseconds(100)); // Simulate resource construction taking time
	}
	
	~some_resource() { cout << "Resource destroyed.\n"; }

	void do_something() {
		if (!is_valid) {
			cout << "\n!!! DATA RACE DETECTED !!!\n";
			cout << "Attempted to use an invalidated resource. Crashing deliberately.\n\n";
			*(int*)nullptr = 0;
		}
		cout << "Resource used successfully.\n";
	}

	void invalidate() { is_valid = false; }
};

shared_ptr<some_resource> resource_ptr;
mutex resource_mutex;

void undefined_behaviour_with_double_checked_locking(const char* thread_name) {
	// DCL (Double-Checked Locking) part to ensure single initialization
	if (!resource_ptr) { // ❶ Point One: Check for initialization OUTSIDE the lock
		cout << thread_name << ": resource_ptr is null at (1)\n";
		lock_guard<mutex> lk(resource_mutex);

		if (!resource_ptr) { // ❷ Point Two: Double-check inside lock
			cout << thread_name << ": resource_ptr still null at (2), creating resource at (3)\n";
			resource_ptr.reset(new some_resource); // ❸
		} else
			cout << thread_name << ": resource_ptr no longer null at (2)\n";
	} else
		cout << thread_name << ": resource_ptr already initialized at (1)\n";

	if (resource_ptr) { // ❹ Point Four: Orchestrate a race condition where one thread invalidates the resource while the other is about to use it. This demonstrates that even if initialization is safe, the subsequent use of the object might not be.
		cout << thread_name << ": at point (4)\n";

		if (strcmp(thread_name, "Thread One") == 0) {
			cout << thread_name << ": waiting 150ms before invalidating...\n"; // Thread 1 will wait, allowing Thread 2 to use the resource once.
			this_thread::sleep_for(chrono::milliseconds(150));

			cout << thread_name << ": INVALIDATING the resource now.\n";
			resource_ptr->invalidate();
		} else { // This is Thread Two
			cout << thread_name << ": waiting 120ms...\n"; // Thread 2 will wait a bit, letting DCL finish and the resource get created.
			this_thread::sleep_for(chrono::milliseconds(120));

			cout << thread_name << ": trying to use resource (first time).\n"; // At this point, the resource is constructed, but not yet invalidated by Thread 1.
			resource_ptr->do_something();

			cout << thread_name << ": waiting 60ms...\n"; // Wait some more. By the time we wake up, Thread 1 will have invalidated the resource.
			this_thread::sleep_for(chrono::milliseconds(60));

			cout << thread_name << ": trying to use resource (second time).\n"; // This second call should happen on an invalidated object, causing a crash.
			resource_ptr->do_something(); // CRASH should happen here
		}
	} else // This part should not be reached
		cout << thread_name << ": resource_ptr still null at (4)\n";
}

int main() {
	print_file_line();
	cout << "Demonstrating use of a resource after its content has been changed (invalidated).\n";
	cout << "A crash indicates the race condition was successfully triggered.\n\n";

	resource_ptr.reset(); // Reset resource_ptr to empty each run for demonstration

	thread t1(undefined_behaviour_with_double_checked_locking, "Thread One");
	thread t2(undefined_behaviour_with_double_checked_locking, "Thread Two");

	t1.join();
	t2.join();

	cout << "\nTest finished. If no crash occurred, the race was not triggered.\n";
}
#endif // MINE