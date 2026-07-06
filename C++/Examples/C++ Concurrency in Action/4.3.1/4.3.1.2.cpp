#ifndef MINE

#include <iostream>
#include <chrono>
#include "../../stdafx.h"	

int main() {
	print_file_line();

	auto start = std::chrono::steady_clock::now(); // Current time from the steady clock
	std::cout << "Starting timer. Now: " << start.time_since_epoch().count() << " nanoseconds\n";
	for (long long i = 0; i < 1000000; ++i); // A simple delay (can be replaced by work)
	auto end = std::chrono::steady_clock::now();
	std::cout << "Ending timer. Now: " << end.time_since_epoch().count() << " nanoseconds\n";
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // Calculate duration in microseconds
	std::cout << "Time elapsed: " << duration.count() << " microseconds\n";

	return 0;
}
#endif //MINE
