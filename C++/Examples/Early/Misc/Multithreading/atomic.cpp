#include "stdafx.h"		  //std::atomic::atomic @ http://www.cplusplus.com/reference/atomic/atomic/atomic/
#include <iostream>       // cout
#include <atomic>         // atomic, atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // thread, this_thread::yield
#include <vector>         // vector
using namespace std;

atomic<bool> ready(false);
atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id) {
	while (!ready) { // wait for the ready signal
		this_thread::yield();
	}
	for (volatile int i = 0; i < 1000000; ++i) { // go!, count to 1 million
	} 
	if (!winner.test_and_set()) { 
		cout << "thread #" << id << " won!\n"; 
	}
};

int main() {
	vector<thread> threads;
	cout << "spawning 10 threads that count to 1 million...\n";
	for (int i = 1; i <= 10; ++i) 
		threads.push_back(thread(count1m, i));
	ready = true;
	for (auto& th : threads) 
		th.join();
	return 0;
}
