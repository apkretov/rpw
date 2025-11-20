#ifdef MINE // Thread-safe lazy initialization with std::call_once

#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include "../../stdafx.h"
using namespace std;

struct some_resource {
	some_resource() {
		cout << "Resource constructed by thread " << this_thread::get_id() << ".\n";
		this_thread::sleep_for(chrono::milliseconds(100)); // Simulate resource construction taking time
	}

	~some_resource() { cout << "Resource destroyed by thread " << this_thread::get_id() << ".\n"; }
	void do_something() { cout << "Resource used by thread " << this_thread::get_id() << ".\n"; }
};

shared_ptr<some_resource> resource_ptr;
once_flag resource_flag; // 1. Replaces the mutex

void init_resource() { // 2. The function to be called exactly once to initialize the resource.
	cout << "init_resource() called by thread " << this_thread::get_id() << ". Creating resource.\n";
	resource_ptr.reset(new some_resource);
}

void use_resource_safely(const char* thread_name) { // The function executed by each thread.
	cout << thread_name << " (" << this_thread::get_id() << "): Calling std::call_once.\n"; 
	call_once(resource_flag, init_resource); // 3. std::call_once replaces the complex and unsafe DCL logic. // It ensures that init_resource() is called exactly once by the first thread that gets here. All other threads will wait here until initialization is complete before proceeding.
	cout << thread_name << " (" << this_thread::get_id() << "): std::call_once has completed.\n";

	cout << thread_name << " (" << this_thread::get_id() << "): Using resource.\n"; 
	resource_ptr->do_something(); // Now it is safe to use the resource.
}

int main() {
	print_file_line();
	cout << "Main Thread (" << this_thread::get_id() << "): Demonstrating thread-safe lazy initialization using std::call_once.\n";

	resource_ptr.reset(); // Reset for demonstration

	thread t1(use_resource_safely, "Thread One");
	thread t2(use_resource_safely, "Thread Two");

	t1.join();
	t2.join();
}
#endif // MINE