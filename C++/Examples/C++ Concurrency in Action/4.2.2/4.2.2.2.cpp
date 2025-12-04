#ifdef MINE

#include <future>
#include <iostream>
#include <thread>
#include <utility>
#include "../../stdafx.h"
using namespace std;

struct foo {
	void operator()() const { cout << "functor operator() called\n"; }
};

void future_use_case() { auto f = async(launch::async, foo{}); }

void packaged_task_use_case() { // Replicates the behavior of future_use_case using packaged_task explicitly for asynchronous task management.
	packaged_task<void()> task(foo{}); // Create a packaged_task bound to foo's operator()
	future<void> f = task.get_future(); // Get the future associated with the task
	thread t(move(task)); // Run the task in a new thread to simulate async behavior
	f.wait(); // Wait for the task to finish
	t.join(); // Join the thread
}

int main() { 
	print_file_line();

	future_use_case();
	packaged_task_use_case();

	return 0;
}
#endif // MINE
