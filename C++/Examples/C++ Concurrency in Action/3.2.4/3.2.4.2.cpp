#ifndef MINE // Model a deadlock situation. Imagine two threads, Thread 1 and Thread 2, and two mutexes, Mutex 1 and Mutex 2. Thread 1 locks Mutex 1 and then tries to lock Mutex 2. At the same time, Thread 2 locks Mutex 2 and then tries to lock Mutex 1. Since Thread 1 is holding Mutex 1 and waiting for Mutex 2, and Thread 2 is holding Mutex 2 and waiting for Mutex 1, neither thread can proceed, resulting in a deadlock.

#include <iostream>
#include <thread>
#include "../../stdafx.h"
using namespace std;

#ifdef STD_MUTEX
#include <mutex>
mutex mutex1;
mutex mutex2;

#else //SIMPLE_MUTEX
class simple_mutex {
public:
	void lock() {
		while (flag.test_and_set(std::memory_order_acquire)) // Atomically tests the flag's current state and sets it to "locked" (true) in one indivisible CPU operation, returning the prior value (true if already locked). // memory_order_acquire: Ensures all prior writes on this thread are visible to others once lock is taken (prevents reordering).
			this_thread::yield(); // Voluntarily yields the CPU core to other threads.
	}

	void unlock() { flag.clear(memory_order_release); } // Atomically sets flag to false (unlocked). // memory_order_release: Ensures all writes done while holding lock are visible to subsequent readers—completes critical section barrier.
private:
	std::atomic_flag flag{};
};

simple_mutex mutex1;
simple_mutex mutex2;
#endif //SIMPLE_MUTEX

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

	jthread t1(thread1Func);
	jthread t2(thread2Func);

	return 0;
}
#endif // MINE
