#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include "../../stdafx.h"
#include "vld.h"
#include "GumballMachineServer.h"
#include "GumballMachineProxy.h"
#include "GumballMonitor.h"

#pragma region Aliases
using io_context            = boost::asio::io_context;
using b_exception           = boost::exception;
using system_error          = boost::system::error_code;
using std::cerr;
using std::cout;
using std::string;
using std::thread;
#pragma endregion

#pragma region Trae
/* 1. Server Side
 - Creates a GumballMachine instance in Seattle with 5 gumballs
 - Sets up a server on port 12345
 - context.run() starts the Boost.Asio event loop, which handles incoming connections */
void runServer(io_context &context) { // Server example
	GumballMachine machine{"Seattle", 5};
    GumballMachineServer server(context, 12345, machine);
    context.run(); // This starts the event loop.
}

/* 2. Client Side
- Creates a proxy that connects to localhost:12345
- Uses the proxy to monitor the remote gumball machine */
void runClient() { // Client example
	io_context context;
	GumballMachineProxy gumballMachineProxy{context, "localhost", 12345};
	GumballMonitor monitor(gumballMachineProxy);
	try {
		monitor.report();
	}
	catch (const b_exception &e) {
		cerr << "Exception: " << diagnostic_information(e) << "\n";
	}
}

/* 3. Main Function
- Creates a separate thread for the server
- Waits briefly to ensure the server is running
- Runs the client
- Performs cleanup by stopping the server and joining the thread
This implementation follows the Proxy Pattern, where GumballMachineProxy acts as a stand-in for the remote GumballMachine, 
allowing the GumballMonitor to work with the machine as if it were local, while actually communicating over the network. */
int main() {
	using namespace std;
	print_file_line();

	io_context context;
	thread server_thread([&context]() { runServer(context); });

	this_thread::sleep_for(chrono::milliseconds(100)); // Give the server a moment to start
	runClient(); // Run client

	context.stop(); // Signal the server to stop and cleanup
	server_thread.join(); // Wait for the server thread to finish
	cout << '\n';

	return 0;
}
#pragma endregion //Trae