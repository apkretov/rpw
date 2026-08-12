#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include "../../stdafx.h"
// OFF #include "vld.h"
#include "GumballMachineServer.h"
#include "GumballMachineProxy.h"
#include "GumballMonitor.h"
#include "GumballConstants.h"

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
static void runServer(io_context_ptr context_ptr) { // Server example
    auto machine_ptr = GumballMachine::create(
        gumball_constants::kDefaultMachineLocation,
        gumball_constants::kDefaultMachineCount);
    GumballMachineServer server(*context_ptr, gumball_constants::kServerPort, machine_ptr);
    context_ptr->run(); // This starts the event loop.
}

static void runClient() { // Client example
	using namespace boost;
	using namespace std;
    io_context io_context_;
    auto GumballMachineProxy_ptr = make_shared<GumballMachineProxy>(
        io_context_,
        gumball_constants::kDefaultServerHost,
        gumball_constants::kServerPort);
    GumballMonitor monitor(GumballMachineProxy_ptr);
    try {
        monitor.report();
    }
    catch (const b_exception &e) {  // This line needs to be updated too
        cerr << "Exception: " << diagnostic_information(e) << "\n";
    }
}

int main() {
    print_file_line();

	using namespace std;

    auto io_context_ptr = make_shared<io_context>();
    jthread server_thread([io_context_ptr]() { runServer(io_context_ptr); });
    
    this_thread::sleep_for(gumball_constants::kServerStartupDelay); // Give the server a moment to start
    runClient(); // Run client
    
    io_context_ptr->stop(); // Signal the server to stop and cleanup
    cout << '\n';

    return 0;
}
#pragma endregion //Trae