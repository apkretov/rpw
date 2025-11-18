#ifdef MINE_DEADLOCK // Avoid calling user-supplied code while holding a lock. User code might acquire locks, causing nested locking and deadlock.
//Deadlock scenario
//Thread 1 holds a lock and calls user code.
//User code tries to acquire the same or another lock already held by Thread 1 or other threads.
//This can create nested locking and cause deadlock.

#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include "../../stdafx.h"
using namespace std;

mutex mtx;

void user_code(function<void()> func) {
	// User code might acquire locks inside here
	func();
}

void thread_func() {
	cout << "Thread locking mutex\n";
	mtx.lock();

	cout << "Calling user-supplied code while holding mutex\n"; // Call user code while holding the lock
	user_code([]() {
		cout << "User code trying to lock mutex\n";
		mtx.lock();  // This causes deadlock because mutex is already locked by this thread
		cout << "User code acquired mutex\n";
		mtx.unlock();
		});

	mtx.unlock();
	cout << "Thread finished\n";
}

int main() {
	print_file_line();

	thread t(thread_func);
	t.join();
	return 0;
}
#endif // MINE_DEADLOCK

#ifdef MINE_SOLUTION // Recommended approach : Avoid calling user code while holding locks. Unlock the mutex before calling user - supplied code. Re-lock only if needed safely afterward.

#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include "../../stdafx.h"
using namespace std;

mutex mtx;

void user_code(function<void()> func) {
	// User code might acquire locks inside here
	func();
}

void thread_func_safe() {
	mtx.lock();
	cout << "Thread locked mutex, preparing to call user code\n";

	mtx.unlock(); // Unlock before calling user code to avoid deadlock

	user_code([]() {
		cout << "User code running without holding mutex\n";
		mtx.lock();
		cout << "User code safely acquired mutex\n";
		mtx.unlock();
		});

	cout << "Thread finished safely\n";
}

int main() {
	print_file_line();

	thread t(thread_func_safe);
	t.join();

	return 0;
}
#endif // MINE_DEADLOCK
