#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include "../../stdafx.h"
// OFF #include "vld.h"
#include "GumballMachineServer.h"
#include "GumballMachineProxy.h"
#include "GumballMonitor.h"

#pragma region Aliases
using b_exception           = boost::exception;
using io_context            = boost::asio::io_context;
using io_context_ptr        = std::shared_ptr<io_context>;
using system_error         = boost::system::error_code;
using std::cerr;
using std::cout;
using std::string;
using std::thread;
#pragma endregion

#pragma region Trae
void runServer(io_context_ptr io_context_) { // Server example
    auto machine = GumballMachine::create("Seattle", 5);
    GumballMachineServer server(*io_context_, 12345, machine);
    io_context_->run(); // This starts the event loop.
}

void runClient() { // Client example
    io_context io_context_;
    auto proxy = std::make_shared<GumballMachineProxy>(io_context_, "localhost", 12345);
    GumballMonitor monitor(proxy);
    try {
        monitor.report();
    }
    catch (const b_exception &e) {  // This line needs to be updated too
        cerr << "Exception: " << boost::diagnostic_information(e) << "\n";
    }
}

int main() {
    print_file_line();

    auto io_context_ = std::make_shared<io_context>();
    thread server_thread([io_context_]() { runServer(io_context_); });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Give the server a moment to start
    runClient(); // Run client
    
    io_context_->stop(); // Signal the server to stop and cleanup
    server_thread.join();
    cout << '\n';

    return 0;
}
#pragma endregion //Trae