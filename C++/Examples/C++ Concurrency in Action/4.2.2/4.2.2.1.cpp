#ifndef MINE

#include <future>
#include <iostream>
#include <vector>
#include <string>
#include "Listing 4.8.h"

std::string example_callback(std::vector<char>* v, int i) { return "Vector size: " + std::to_string(v->size()) + ", int: " + std::to_string(i); }

void unspecialized_function() { std::cout << "This is an unspecialized function.\n"; }

int main() {
	std::vector<char> data = {'a', 'b', 'c'};

	std::packaged_task<std::string(std::vector<char>*, int)> special_task(example_callback); // Now uses your specialized version!
	std::packaged_task<void() > general_task(unspecialized_function);
	std::future<std::string> result = special_task.get_future();

	special_task(&data, 42); // Call the task (typically in another thread)

	std::cout << result.get() << '\n';

	general_task();

	return 0;
}
#endif // MINE