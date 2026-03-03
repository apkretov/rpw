#ifdef MINE // Model a deadlock situation. Imagine two threads, Thread 1 and Thread 2, and two mutexes, Mutex 1 and Mutex 2. Thread 1 locks Mutex 1 and then tries to lock Mutex 2. At the same time, Thread 2 locks Mutex 2 and then tries to lock Mutex 1. Since Thread 1 is holding Mutex 1 and waiting for Mutex 2, and Thread 2 is holding Mutex 2 and waiting for Mutex 1, neither thread can proceed, resulting in a deadlock.

#include <iostream>
#include <thread>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

mutex mutex1;
mutex mutex2;

void thread1Func() {
	cout << "Thread 1: Locking mutex1...\n";
	mutex1.lock();
	this_thread::sleep_for(chrono::milliseconds(100)); // simulate work
	cout << "Thread 1: Waiting to lock mutex2...\n";
	mutex2.lock();

	cout << "Thread 1: Locked mutex2\n"; // This point is never reached in a deadlock scenario

	mutex2.unlock();
	mutex1.unlock();
}

void thread2Func() {
	cout << "Thread 2: Locking mutex2...\n";
	mutex2.lock();
	this_thread::sleep_for(chrono::milliseconds(100)); // simulate work
	cout << "Thread 2: Waiting to lock mutex1...\n";
	mutex1.lock();

	cout << "Thread 2: Locked mutex1\n"; // This point is never reached in a deadlock scenario

	mutex1.unlock();
	mutex2.unlock();
}

int main() {
	print_file_line();

	thread t1(thread1Func);
	thread t2(thread2Func);

	t1.join();
	t2.join();

	return 0;
}
#endif // MINE
