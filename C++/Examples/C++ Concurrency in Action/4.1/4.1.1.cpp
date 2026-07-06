#if 0

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <print>
#include <thread>
#include "../../stdafx.h"
using namespace std;

bool flag = false;
mutex m;
condition_variable cv;

void wait_for_flag() {
	int count = 0;
	unique_lock lk(m);
	print("[wait_for_flag] Waiting for flag...\n"); //MINE
	while (!flag) {
		lk.unlock(); // Unlock before sleeping
		print("[wait_for_flag] Sleeping {}...\n", ++count); //MINE
		this_thread::sleep_for(chrono::milliseconds(100)); // Sleep 100 ms
		lk.lock();   // Relock mutex
	}
	print("[wait_for_flag] Flag is true, continuing...\n"); //MINE
}

#pragma region MINE
void wait_with_condition_variable() {
	unique_lock lk(m);
	print("[wait_with_condition_variable] Waiting for flag...\n");
	cv.wait(lk, [] { return flag; }); // Wait until flag is true
	print("[wait_with_condition_variable] Flag is {}, continuing...\n", flag);
}

void setter_thread() {
	print("[setter_thread] Sleeping for 1 second...\n");
	this_thread::sleep_for(chrono::seconds(1)); // Simulate work
	{
		lock_guard lk(m);
		flag = true;
		print("[setter_thread] Flag set to {}.\n", flag);
	}
	cv.notify_one(); // Notify waiting thread on condition variable
}

int main() {
	print_file_line();

	flag = false; // Test with sleeping while waiting // Reset flag 
	jthread waiter1(wait_for_flag);
	jthread setter1(setter_thread);
	waiter1.join();
	setter1.join();

	cout << "--------\n";

	flag = false; // Test with condition variable waiting // Reset flag 
	jthread waiter2(wait_with_condition_variable);
	jthread setter2(setter_thread);

	return 0;
}
#pragma endregion //MINE  
#endif // 1
