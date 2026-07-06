#if 0

#include <thread>
#include "../../stdafx.h"
#include "Listing 2.1.h"

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();
}

int main() {
	print_file_line();
	oops();
}
#endif