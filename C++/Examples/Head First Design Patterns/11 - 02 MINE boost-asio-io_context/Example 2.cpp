#ifdef MINE

/*
2. Using io_context as a simple thread - safe task queue
You can post work from anywhere, then run io_context in one or more threads.
Points:
Multiple threads can call io.run() on the same io_context.
Tasks are distributed among threads automatically.
This is how you scale handling of many connections across CPU cores.
*/

#include <boost/asio.hpp>
#include <print>
#include <thread>
#include <vector>
#include "../../stdafx.h"

int main() {
	print_file_line();

	boost::asio::io_context io;

	for (int i = 0; i < 10; ++i) // Post 10 tasks
		boost::asio::post(io, [i] { std::println("Task {} on thread {}", i, std::this_thread::get_id()); });

	std::vector<std::jthread> threads; // Run io_context on 3 threads
	for (int i = 0; i < 3; ++i)
		threads.emplace_back([&io] { io.run(); });

	return 0;
}
#endif //MINE
