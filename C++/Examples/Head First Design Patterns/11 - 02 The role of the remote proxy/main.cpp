#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include "../../stdafx.h"
//OFF #include "vld.h"
#include "GumballMachine.h"
#include "GumballMachineServer.h"
#include "GumballMachineProxy.h"
#include "GumballMonitor.h"

#pragma region Trae
void runServer() { // Server example
    boost::asio::io_context io_context;
    auto machine = GumballMachine::create("Seattle", 5);
    GumballMachineServer server(io_context, 12345, machine);
    io_context.run();
}

void runClient() { // Client example
    boost::asio::io_context io_context;
    auto proxy = std::make_shared<GumballMachineProxy>(io_context, "localhost", 12345);
    GumballMonitor monitor(proxy);
	try {
		monitor.report();
	}
	catch (const boost::exception &e) {
		std::cerr << "Exception: " << boost::diagnostic_information(e) << "\n";
	}
}

int main() {
	print_file_line();

	std::thread server_thread(runServer); // Run server in a separate thread
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Give the server a moment to start
	runClient(); // Run client
	server_thread.join(); // Cleanup

    return 0;
}
#pragma endregion //Trae