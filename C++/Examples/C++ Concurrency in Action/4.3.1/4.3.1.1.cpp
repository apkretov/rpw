#ifdef MINE

#include <iostream>
#include <chrono>

int main() {
	auto current_time = std::chrono::steady_clock::now(); // 1. Get the current time
	std::chrono::steady_clock::time_point p = current_time; // 2. Type used for time representation (implicitly shown through 'current_time')
	std::chrono::steady_clock::period tick_period; // 3. Tick period of the clock
	bool is_clock_steady = std::chrono::steady_clock::is_steady; // 4. Whether the clock is steady

	std::cout << "Current time (steady_clock): " << current_time.time_since_epoch().count() << " ticks since epoch\n"; // Print the current time in ticks
	std::cout << "Time point type: " << typeid(p).name() << '\n'; // Print the type of the time point
	std::cout << "is_steady: " << (is_clock_steady ? "true" : "false") << '\n'; // Print some information to verify behavior
	std::cout << "Tick period: " << tick_period.num << '/' << tick_period.den << " seconds per tick\n";

	return 0;
}
#endif //MINE
