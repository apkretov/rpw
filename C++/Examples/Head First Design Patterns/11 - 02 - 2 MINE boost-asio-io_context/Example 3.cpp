#ifdef MINE

/*
3. Adding a timer : real asynchronous behavior
Now we use a timer to show “do something later” without blocking.

Flow:
async_wait starts the timer and returns immediately.
The lambda is registered as a handler to be called later.
io.run() blocks and waits for events (here: timer expiry).
After ~2 seconds, the handler runs, prints “Timer fired!”, then run() exits because there’s no more work.
*/

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include "../../stdafx.h"

int main() {
	print_file_line();

	boost::asio::io_context io;

	boost::asio::steady_timer timer(io);
	timer.expires_after(std::chrono::seconds{2}); // Start an async timer: call the lambda after 2 seconds

	timer.async_wait([](const boost::system::error_code& ec) {
		if (!ec)
			std::cout << "Timer fired!\n";
	});

	std::cout << "Timer started, waiting...\n";
	io.run(); // Run the event loop to process tasks from the queue in the order they arrived.
	std::cout << "Done\n";

	return 0;
}
#endif //MINE
