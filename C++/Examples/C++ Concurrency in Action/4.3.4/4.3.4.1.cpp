#ifdef MINE

// Table 4.1 Row 1: std::this_thread Namespace
//	 Functions Covered: sleep_for( duration ), sleep_until( time_point )
//	 Return Values: N/A

#include <iostream>
#include <thread>
#include <chrono>
#include "../../stdafx.h"

int main() {
	print_file_line();

	std::cout << "--- Table 4.1 Row 1: std::this_thread Examples ---\n";

	std::cout << "1. Testing sleep_for (waiting 1.5 seconds)...\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	std::cout << "2. Testing sleep_until (waiting until 1 second in the future)...\n";
	auto wake_time = std::chrono::system_clock::now() + std::chrono::seconds(1);
	std::this_thread::sleep_until(wake_time);

	std::cout << "Row 1 execution complete.\n";
	return 0;
}
#endif //MINE
