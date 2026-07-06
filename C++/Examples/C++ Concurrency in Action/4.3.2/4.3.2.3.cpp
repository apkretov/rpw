#if 0

#include <iostream>
#include <chrono>
#include "../../stdafx.h"

std::chrono::milliseconds ms(54802);
std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);

using namespace std::chrono_literals;
auto two_seconds = 1s + 1s; // Durations support arithmetic
auto ten_seconds = 2 * 5s; // Example multiplying by a constant
auto count_of_ms = std::chrono::milliseconds(1234).count(); // Explicitly getting the count of milliseconds

#pragma region MINE
int main() { // Example to show values (converting to seconds for printing)
	print_file_line();

	std::cout << "Milliseconds: " << ms.count() << "\n"; // The result is truncated, so s will have a value of 54.
	std::cout << "Truncated seconds: " << s.count() << "\n\n";

	std::cout << "Count of 10 seconds: " << ten_seconds.count() << "\n";
	std::cout << "Explicit milliseconds count: " << count_of_ms << "\n";

	return 0;
}
#pragma endregion 
#endif // 1
