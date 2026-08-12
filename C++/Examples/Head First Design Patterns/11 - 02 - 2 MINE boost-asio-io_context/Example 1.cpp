#ifdef MINE

/*
1. Minimal example : just posting tasks
This shows the core idea without any sockets.
Key idea : io_context is where work gets executed. If you don’t call run(), nothing happens.
*/

#include <boost/asio.hpp>
#include <iostream>
#include "../../stdafx.h"

int main() {
	print_file_line();

	boost::asio::io_context		io;  // the event loop / task manager

	boost::asio::post(io, [] { std::cout << "Task 1\n"; }); // Post two tasks (lambdas) to be run by io_context
	boost::asio::post(io, [] { std::cout << "Task 2\n"; });

	std::cout << "Before run()\n";
	io.run(); // Run the event loop until there is no more work
	std::cout << "After run()\n";

	return 0;
}
#endif //MINE
