#include "stdafx.h" //atomic_flag @ http://en.cppreference.com/w/cpp/atomic/atomic_flag
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
using namespace std;

atomic_flag lock = ATOMIC_FLAG_INIT; //Initialization of atomic flag. This macro is defined in such a way that it can be used to initialize an object of type atomic_flag to the clear state. @ http://www.cplusplus.com/reference/atomic/ATOMIC_FLAG_INIT/

void f(int n) {
	for (int cnt = 0; cnt < 100; ++cnt) {
		while (lock.test_and_set(memory_order_acquire))  // acquire lock
			; // spin
		cout << "Output from thread " << n << '\n';
		lock.clear(memory_order_release);               // release lock
	}
}

void fMyTest(int n) {
	while (lock.test_and_set(memory_order_acquire)) {
	}
	for (int cnt = 0; cnt < 100; ++cnt) {
		cout << "Output from thread " << n << '\n';
	}
	lock.clear(memory_order_release);
}

int main() {
	vector<thread> v;
	for (int n = 0; n < 10; ++n)
		v.emplace_back(f/*TEST fMyTest*/, n);
	for (auto& t : v) 
		t.join();
}