#include "stdafx.h" //atomic_flag @ http://en.cppreference.com/w/cpp/atomic/atomic_flag
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
using namespace std;

atomic_flag lock = ATOMIC_FLAG_INIT;

void f(int n) {
	for (int cnt = 0; cnt < 100; ++cnt) {
		while (lock.test_and_set(memory_order_acquire))  // acquire lock
			; // spin
		cout << "Output from thread " << n << '\n';
		lock.clear(memory_order_release);               // release lock
}	}

int main() {
	vector<thread> v;
	for (int n = 0; n < 10; ++n) v.emplace_back(f, n);	
	for (auto& t : v) t.join(); 
}