#ifdef MINE

#include <future>
#include "../../stdafx.h"
#include "listing_4.7.h"

int main() { 
	print_file_line(); //MINE

	X x;
	auto f6 = std::async(std::launch::async, Y(), 1.2); // Run in new thread
	auto f7 = std::async(std::launch::deferred, baz, std::ref(x)); // Run in wait() or get()
	auto f8 = std::async(std::launch::deferred | std::launch::async, baz, std::ref(x)); // Implementation chooses
	auto f9 = std::async(baz, std::ref(x)); // Implementation chooses
	f7.wait(); // Invoke deferred function
}
#endif //MINE