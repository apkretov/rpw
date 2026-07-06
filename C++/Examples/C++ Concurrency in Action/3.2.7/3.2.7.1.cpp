#if 0

#include <iostream>
#include <mutex>
#include <thread>
#include "../../stdafx.h"

std::mutex some_mutex; // Global mutex to protect shared resources

void prepare_data() {
	std::cout << "Thread " << std::this_thread::get_id() << " Preparing data...\n";
	// Simulate data preparation work
}

void do_something() {
	std::cout << "Thread " << std::this_thread::get_id() << " Doing something with prepared data...\n";
	// Simulate further processing under lock
}

std::unique_lock<std::mutex> get_lock() { // Function locks the mutex and returns the lock to caller
	std::unique_lock<std::mutex> lk(some_mutex); // Lock mutex
	prepare_data();                              // Prepare data under lock
	return lk;                                   // Transfer lock ownership to caller
}

void process_data() {
	std::unique_lock<std::mutex> lk(get_lock()); // Receive ownership of lock returned by get_lock()
	do_something(); // Receive ownership of lock returned by get_lock()
	// Lock is released when lk goes out of scope
}

int main() {
	print_file_line();

	std::jthread t1(process_data);
	std::jthread t2(process_data);

	return 0;
}
#endif // 1