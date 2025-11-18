#include <iostream> // Avoid nested locks. Don’t lock another mutex if you already hold one. This prevents deadlock from lock use alone. If multiple locks are needed, acquire them together with std::lock to avoid deadlock.
#include <thread>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

mutex mutex2;
mutex mutex1;

#ifndef MINE_DEADLOCK // Deadlock due to nested locks // When Thread A locks mutex 1 and waits to lock mutex 2 while Thread B locks mutex 2 and waits to lock mutex 1, a deadlock occurs.
void thread1_func() {
	cout << "Thread 1 locking mutex1\n";
	mutex1.lock();
	cout << "Thread 1 locked mutex1\n";

	this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work

	cout << "Thread 1 trying to lock mutex2\n";
	mutex2.lock();  // Deadlock if thread2 holds mutex2
	cout << "Thread 1 locked mutex2\n";

	mutex2.unlock();
	mutex1.unlock();
}

void thread2_func() {
	cout << "Thread 2 locking mutex2\n";
	mutex2.lock();
	cout << "Thread 2 locked mutex2\n";

	this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work

	cout << "Thread 2 trying to lock mutex1\n";
	mutex1.lock();  // Deadlock if thread1 holds mutex1
	cout << "Thread 2 locked mutex1\n";

	mutex1.unlock();
	mutex2.unlock();
}

int main() {
	print_file_line();

	thread t1(thread1_func);
	thread t2(thread2_func);

	t1.join();
	t2.join();

	return 0;
}
#endif // MINE_DEADLOCK

#ifdef MINE_STDLOCK // Recommended solution: use std::lock. Using std::lock(mutex1, mutex2) ensures both mutexes are locked together atomically, preventing deadlock. Unlocking is done afterward normally.
void thread1_func_safe() {
	std::cout << "Thread 1 locking mutex1 and mutex2 safely\n";
	std::lock(mutex1, mutex2);
	std::cout << "Thread 1 locked mutex1 and mutex2\n";

	mutex1.unlock();
	mutex2.unlock();
}

void thread2_func_safe() {
	std::cout << "Thread 2 locking mutex1 and mutex2 safely\n";
	std::lock(mutex1, mutex2);
	std::cout << "Thread 2 locked mutex1 and mutex2\n";

	mutex1.unlock();
	mutex2.unlock();
}

int main() {
	std::thread t1(thread1_func_safe);
	std::thread t2(thread2_func_safe);

	t1.join();
	t2.join();

	return 0;
}
#endif // MINE_STDLOCK