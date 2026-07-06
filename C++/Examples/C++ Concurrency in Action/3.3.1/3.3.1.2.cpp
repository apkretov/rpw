#ifdef MINE // Problematic double-checked locking - Demonstrating use-after-invalidation
/* What can happen
 Both threads check resource_ptr at ❶ and see nullptr.
 Both enter the mutex — one waits for the other.
 The first thread to lock creates the resource at ❸.
 After the first thread exits, the second thread enters the locked section at ❷, sees resource_ptr is now non-null, and continues.
 Both threads end up using resource_ptr at ❹.
 If resource_ptr's ownership or content changes between these steps (for instance, if the resource could be reset or destroyed in another context), the second thread could access an invalid or partially constructed object, leading to undefined behavior or a crash.
 */
#include "../../stdafx.h"
#include <chrono>
#include <memory>
#include <mutex>
#include <print>
#include <string_view>
#include <thread>
using namespace std;

class some_resource {
public:
	some_resource() {
		print("Resource constructed.\n");
		this_thread::sleep_for(chrono::milliseconds(100)); // Simulate resource construction taking time
	}

	~some_resource() { print("Resource destroyed.\n"); }

	void do_something() const {
		if (!is_valid) {
			print("\n!!! DATA RACE DETECTED !!!\n");
			print("Attempted to use an invalidated resource. Crashing deliberately.\n\n");
			*static_cast<int*>(nullptr) = 0;
		}
		print("Resource used successfully.\n");
	}

	void invalidate() { is_valid = false; }
private:
	bool is_valid = true;
};

shared_ptr<some_resource> resource_ptr;
mutex resource_mutex;
constexpr string_view thread_one = "Thread One";
constexpr string_view thread_two = "Thread Two";

void undefined_behaviour_with_double_checked_locking(string_view thread_name) {
	// DCL (Double-Checked Locking) part to ensure single initialization
	if (!resource_ptr) { // ❶ Point One: Check for initialization OUTSIDE the lock
		print("{}: resource_ptr is null at (1)\n", thread_name);
		lock_guard lk(resource_mutex);

		if (!resource_ptr) { // ❷ Point Two: Double-check inside lock
			print("{}: resource_ptr still null at (2), creating resource at (3)\n", thread_name);
			resource_ptr.reset(new some_resource); // ❸
		} else
			print("{}: resource_ptr no longer null at (2)\n", thread_name);
	} else
		print("{}: resource_ptr already initialized at (1)\n", thread_name);

	if (resource_ptr) { // ❹ Point Four: Orchestrate a race condition where one thread invalidates the resource while the other is about to use it. This demonstrates that even if initialization is safe, the subsequent use of the object might not be.
		print("{}: at point (4)\n", thread_name);

		if (thread_name == thread_one) {
			print("{}: waiting 150ms before invalidating...\n", thread_name); // Thread 1 will wait, allowing Thread 2 to use the resource once.
			this_thread::sleep_for(chrono::milliseconds(150));

			print("{}: INVALIDATING the resource now.\n", thread_name);
			resource_ptr->invalidate();
		} else { // This is Thread Two
			print("{}: waiting 120ms...\n", thread_name); // Thread 2 will wait a bit, letting DCL finish and the resource get created.
			this_thread::sleep_for(chrono::milliseconds(120));

			print("{}: trying to use resource (first time).\n", thread_name); // At this point, the resource is constructed, but not yet invalidated by Thread 1.
			resource_ptr->do_something();

			print("{}: waiting 60ms...\n", thread_name); // Wait some more. By the time we wake up, Thread 1 will have invalidated the resource.
			this_thread::sleep_for(chrono::milliseconds(60));

			print("{}: trying to use resource (second time).\n", thread_name); // This second call should happen on an invalidated object, causing a crash.
			resource_ptr->do_something(); // CRASH should happen here
		}
	} else // This part should not be reached
		print("{}: resource_ptr still null at (4)\n", thread_name);	
}

int main() {
	print_file_line();

	print("Demonstrating use of a resource after its content has been changed (invalidated).\n");
	print("A crash indicates the race condition was successfully triggered.\n\n");

	resource_ptr.reset(); // Reset resource_ptr to empty each run for demonstration

	jthread t1(undefined_behaviour_with_double_checked_locking, thread_one);
	jthread t2(undefined_behaviour_with_double_checked_locking, thread_two);

	t1.join();
	t2.join();

	print("\nTest finished. If no crash occurred, the race was not triggered.\n");
}
#endif // MINE