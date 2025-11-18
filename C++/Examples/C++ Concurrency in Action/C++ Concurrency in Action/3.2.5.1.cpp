#ifdef MINE // Deadlock often happens with locks, but it can also occur without locks, such as when two threads each wait by calling join() on the other. Neither thread can proceed because both are waiting for the other to finish, creating a deadlock. This can happen with more than two threads forming a cycle of waiting. The key to avoiding deadlock is: never wait for a thread that might be waiting for you.
// To model a deadlock in C++ caused by threads each waiting on the other with join(), consider creating two threads where each tries to join the other thread. This will simulate a deadlock scenario due to cyclic waiting.
// Explanation:
// Both threads wait indefinitely for the other thread to finish, creating a deadlock.
// The main thread does not join either thread, so the program may deadlock (or terminate depending on environment).
// This models deadlock without any locks but via cyclic join() waits.
// Key point:
// To avoid this kind of deadlock, a thread should never wait on a thread that may be waiting on it, preventing the cycle of dependencies.
#include <iostream>
#include <thread>
#include <chrono>
#include "../../stdafx.h"
using namespace std;

thread t1;
thread t2;

void thread1_func() {
	cout << "Thread 1 started\n";
	if (t2.joinable()) { // Thread 1 waits for thread 2 to finish
		cout << "Thread 1 waiting for Thread 2\n";
		t2.join();  // This blocks thread 1
	}
	cout << "Thread 1 finished\n";
}

void thread2_func() {
	cout << "Thread 2 started\n";
	if (t1.joinable()) { // Thread 2 waits for thread 1 to finish
		cout << "Thread 2 waiting for Thread 1\n";
		t1.join();  // This blocks thread 2
	}
	cout << "Thread 2 finished\n";
}

int main() {
	print_file_line();

	t1 = thread(thread1_func);
	t2 = thread(thread2_func);

	this_thread::sleep_for(chrono::seconds(1)); // Main thread does not join here to simulate deadlock
	cout << "Main thread exiting without joining\n";

	return 0;
}

#endif // MINE
