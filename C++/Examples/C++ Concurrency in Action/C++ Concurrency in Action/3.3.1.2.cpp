#if 1 // Problematic double-checked locking
// What can happen
// Both threads check resource_ptr at ❶ and see nullptr.
// Both enter the mutex—one waits for the other.
// The first thread to lock creates the resource at ❸.
// After the first thread exits, the second thread enters the locked section at ❷, sees resource_ptr is now non-null, and continues.
// Both threads end up using resource_ptr at ❹.
//If resource_ptr's ownership or content changes between these steps (for instance, if the resource could be reset or destroyed in another context), the second thread could access an invalid or partially constructed object, leading to undefined behavior or a crash.
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include "../../stdafx.h"
using namespace std;

struct some_resource {
	some_resource() { cout << "Resource constructed.\n"; }
	~some_resource() { cout << "Resource destroyed.\n"; }
	void do_something() { cout << "Resource used.\n"; }
};

shared_ptr<some_resource> resource_ptr;
mutex resource_mutex;

void undefined_behaviour_with_double_checked_locking(const char* thread_name) {
	if (!resource_ptr) { // ❶ Point One: Check for initialization OUTSIDE the lock
		cout << thread_name << ": resource_ptr is null at ❶\n";
		lock_guard<mutex> lk(resource_mutex);

		if (!resource_ptr) { // ❷ Point Two: Double-check inside lock
			cout << thread_name << ": resource_ptr still null at ❷, creating resource at ❸\n";
			resource_ptr.reset(new some_resource); // ❸
			this_thread::sleep_for(chrono::milliseconds(100)); // Simulate resource construction taking time
		} else
			cout << thread_name << ": resource_ptr no longer null at ❷\n";
	} else
		cout << thread_name << ": resource_ptr already initialized at ❶\n";

	if (resource_ptr) { // ❹ Point Four: Attempt to use the resource
		cout << thread_name << ": using resource_ptr at ❹\n";
		resource_ptr->do_something();
	} else
		cout << thread_name << ": resource_ptr still null at ❹\n";
}

int main() {
	print_file_line();

	resource_ptr.reset(); // Reset resource_ptr to empty each run for demonstration

	thread t1(undefined_behaviour_with_double_checked_locking, "Thread One");
	this_thread::sleep_for(chrono::milliseconds(20)); // Give Thread One a head start to hit the race condition window
	thread t2(undefined_behaviour_with_double_checked_locking, "Thread Two");

	t1.join();
	t2.join();
}
#endif // 1
