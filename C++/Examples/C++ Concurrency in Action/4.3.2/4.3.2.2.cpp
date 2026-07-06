#if 0

#include <iostream>
#include <chrono>
#include "../../stdafx.h"

using namespace std::chrono_literals;

auto one_day = 24h;
auto half_an_hour = 30min;
auto max_time_between_messages = 30ms;
auto float_min = 2.5min; // 2.5min will be std::chrono::duration<some-floating-point-type, std::ratio<60,1>>

#pragma region MINE
int main() { // Example to show values (converting to seconds for printing)
	print_file_line();

	std::cout << "One day in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(one_day).count() << "s\n";
	std::cout << "Half an hour in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(half_an_hour).count() << "s\n";
	std::cout << "2.5min is " << float_min.count() << " minutes (floating point)\n"; // Show floating point value

	return 0;
}
#pragma endregion 
#endif // 1
