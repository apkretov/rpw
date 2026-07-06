#ifdef MINE_UNSAFE //## Race in Stack Interface(empty() / top() / pop()) // Version 1: Unsafe std::stack(races, prints same value twice or discard) * *
//** Problem** : `if (!empty()) {
//	top(); pop();
//}` races between calls.

#include <chrono>
#include <print>
#include <stack>
#include <thread>
#include "../../stdafx.h"

std::stack<int> s;

void consumer() {
	std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Stagger
	if (!s.empty()) {
		int value = s.top();
		s.pop();
		std::print("Thread ID {} Consumed: {}\n", std::this_thread::get_id(), value);
	}
}

int main() {
	print_file_line();

	s.push(2);
	s.push(1);
	std::jthread t1(consumer);
	std::jthread t2(consumer);

	return 0;
}
//** Output example** : "Consumed: 1" twice(discard 2) or same value twice.
#endif // MINE_UNSAFE

#ifdef MINE_SAFE 

#include <functional>
#include <memory>
#include <print>
#include <thread>
#include "Listing 3.5.h"
#include "../../stdafx.h"

void consumer(ThreadSafeStack<int>& stack) {
	try {
		auto ptr = stack.pop();  // Atomic pop+get
		std::print("Thread ID {} Consumed: {}\n", std::this_thread::get_id(), *ptr);
	}
	catch (const EmptyStack&) {
		std::print("Thread ID {} Empty!\n", std::this_thread::get_id());
	}
}

int main() {
	print_file_line();

	ThreadSafeStack<int> stack;
	stack.push(2);
	stack.push(1);
	std::jthread t1(consumer, std::ref(stack));
	std::jthread t2(consumer, std::ref(stack));
	t1.join(); 
	t2.join();
	std::print("No races/duplicates\n");

	return 0;
}

//** Output** : Each consumes unique value(1 and 2), no races / loss.

//## Granularity Tradeoffs Demo

//* *Too coarse(global lock) * *: Serializes all access.

// Omitted: single global mutex for all stacks slows concurrency.

//* *Too fine * *: Races shown above.Balance with atomic compound ops.[studylib](https ://studylib.net/doc/27734771/c---concurrency-in-action--2nd-edition)
#endif // MINE_SAFE
