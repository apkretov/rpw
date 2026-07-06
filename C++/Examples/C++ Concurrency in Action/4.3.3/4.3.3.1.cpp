#if 0

#include <chrono>
#include <iostream>
#include "../../stdafx.h"

#pragma region MINE
void func1() { // Define and inspect a time_point
	using Clock = std::chrono::system_clock;
	using Sec = std::chrono::seconds;
	auto tp = std::chrono::time_point<Clock, Sec>(Sec(0)); // epoch
	auto since = tp.time_since_epoch(); // Sec
	std::cout << since.count() << " seconds since epoch\n";
}

void func2() { // Use a different clock and duration units
	using Steady = std::chrono::steady_clock; // often uses boot-based epoch
	using MilliSec = std::chrono::milliseconds;
	auto tp = std::chrono::time_point<Steady, MilliSec>(MilliSec(5000)); // 5s after epoch
	std::cout << tp.time_since_epoch().count() << " ms since steady_clock epoch\n";
}

void func3() { // Get current time and duration since epoch
	auto now = std::chrono::system_clock::now(); // time_point<system_clock>
	auto dur = now.time_since_epoch(); // duration in system_clock::duration
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
	std::cout << ms.count() << " ms since epoch\n";
}

void func4() { // Convert between clocks that share an epoch (example assumes compatible epochs)
	using Clock = std::chrono::system_clock;
	using Sec = std::chrono::seconds;
	auto now = std::chrono::system_clock::now();
	std::chrono::time_point<Clock, Sec> tp_sec = std::chrono::time_point_cast<Sec>(now); // represent same instant using system_clock::time_point with seconds resolution
	std::cout << tp_sec.time_since_epoch().count() << " seconds since epoch\n";
}

void func5() { // Add a duration to a time_point
	auto now = std::chrono::high_resolution_clock::now();
	auto future_time = now + std::chrono::nanoseconds(500);
	std::cout << future_time.time_since_epoch().count() << " nanoseconds since high_resolution_clock epoch\n";
}

void do_something() { for (volatile int i = 0; i < 10000; ++i); } // Simulate some work
#pragma endregion //MINE

void func6() { // Subtract one time point from another 
	auto start = std::chrono::high_resolution_clock::now();
	do_something();
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "do_something() took " << std::chrono::duration<double>(stop - start).count() << " seconds" << std::endl;
}

int main() { //MINE
	print_file_line();

	func1();
	func3();
	func2();
	func4();
	func5();
	func6();

	return 0;
}
#endif //1
