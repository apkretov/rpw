#if 0

#include <iostream>
#include <chrono>
#include "../../stdafx.h"

std::chrono::duration<short, std::ratio<60, 1>> five_min(5); // Defines 5 minutes stored as a short int // std::ratio<60, 1> specifies 60 seconds per unit (1 minute)
std::chrono::duration<double, std::ratio<1, 1000>> double_ms(2.5); // A count of milliseconds stored in a double
std::chrono::duration<double, std::centi> double_centi(10.0); // Custom duration with SI ratio

using atto_duration = std::chrono::duration<double, std::atto>; // SI ratios from std::atto to std::exa

#pragma region MINE
int main() {
	print_file_line();

	std::cout << "Duration count: " << five_min.count() << " minutes\n";
	std::cout << "Double ms duration count: " << double_ms.count() << " milliseconds\n"; // Display counts

	auto in_seconds = std::chrono::duration_cast<std::chrono::seconds>(five_min); // Converting minutes to standard seconds duration
	std::cout << "5 minutes is equivalent to: " << in_seconds.count() << " seconds\n";

	return 0;
}
#pragma region MINE
#endif //1
