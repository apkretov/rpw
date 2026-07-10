#include "message_queue.h"
#include "dispatcher.h"
#include "messages.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "../../stdafx.h"

static void worker_thread(message_queue* q) {
	try {
		for (;;)
			dispatcher(q) // Evaluates the temporary instantiation hierarchy chain, then executes the outermost unchained destructor loop.
				.handle<MsgA>([](MsgA const& msg) { std::cout << "[Worker] Handled MsgA: " << msg.text << std::endl; })
				.handle<MsgB>([](MsgB const& msg) { std::cout << "[Worker] Handled MsgB: " << msg.value << std::endl; });
	}
	catch (close_queue const&) {
		std::cout << "[Worker] Caught close_queue exception. Thread terminating." << std::endl;
	}
}

int main() {
	print_file_line();

	message_queue q;
	std::jthread t(worker_thread, &q);

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	q.push(MsgA{"Hello Splitted Framework!"});

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	q.push(MsgB{999});

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	q.push(close_queue{});

	return 0;
}