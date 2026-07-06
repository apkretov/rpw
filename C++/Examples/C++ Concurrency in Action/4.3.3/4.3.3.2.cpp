#ifndef MINE

#include <iostream>
#include <thread>
#include "Listing 4.11.h"	
#include "../../stdafx.h"

void func1() { // The clock in a time_point affects wait durations when the system clock changes.
	using namespace std::chrono_literals; 
	std::cout << "Waiting...\n";
	auto timeout = std::chrono::system_clock::now() + 1s;
	std::this_thread::sleep_until(timeout);
	std::cout << "Wait finished.\n\n";
}

void func2() {
	std::cout << "Starting the wait...\n";
	std::jthread t([] {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::scoped_lock lk(m);
		done = true;
		cv.notify_one();
		std::cout << "Notified!\n";
	});

	bool result = wait_loop();
	std::cout << "Wait finished. Done = " << std::boolalpha << result << '\n';
}

int main() {
	print_file_line();

	func1();
	func2();

	return 0;
}
#endif //MINE