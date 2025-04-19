#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include "../../stdafx.h"
//OFF #include "vld.h"
#include "GumballMachineServer.h"
#include "GumballMachineProxy.h"
#include "GumballMonitor.h"

#pragma region Aliases
using io_context            = boost::asio::io_context;
using b_exception           = boost::exception;
using io_context_ptr        = std::shared_ptr<io_context>;
using system_error          = boost::system::error_code;
using std::cerr;
using std::cout;
using std::string;
using std::thread;
#pragma endregion

#pragma region Trae
void runServer(io_context_ptr context_ptr) { // Server example
    auto machine_ptr = GumballMachine::create("Seattle", 5);
    GumballMachineServer server(*context_ptr, 12345, machine_ptr);
    context_ptr->run(); // This starts the event loop.
}

void runClient() { // Client example
	using namespace boost;
	using namespace std;
    io_context io_context_;
    auto GumballMachineProxy_ptr = make_shared<GumballMachineProxy>(io_context_, "localhost", 12345);
    GumballMonitor monitor(GumballMachineProxy_ptr);
    try {
        monitor.report();
    }
    catch (const b_exception &e) {  // This line needs to be updated too
        cerr << "Exception: " << diagnostic_information(e) << "\n";
    }
}

int main() {
	using namespace std;
    print_file_line();

    auto io_context_ptr = make_shared<io_context>();
    thread server_thread([io_context_ptr]() { runServer(io_context_ptr); });
    
    this_thread::sleep_for(chrono::milliseconds(100)); // Give the server a moment to start
    runClient(); // Run client
    
    io_context_ptr->stop(); // Signal the server to stop and cleanup
	server_thread.join(); // Wait for the server thread to finish
    cout << '\n';

    return 0;
}
#pragma endregion //Trae