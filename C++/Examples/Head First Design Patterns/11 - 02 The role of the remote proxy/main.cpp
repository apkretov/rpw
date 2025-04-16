#include <boost/asio.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/exception.hpp>
#include "../../stdafx.h"
#include "vld.h"
#include "GumballMachine.h"
#include "GumballMachineServer.h"
#include "GumballMachineProxy.h"
#include "GumballMonitor.h"

#pragma region Trae
void runServer(std::shared_ptr<boost::asio::io_context> io_context) { // Server example
    auto machine = GumballMachine::create("Seattle", 5);
    GumballMachineServer server(*io_context, 12345, machine);
    io_context->run();
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

    auto io_context = std::make_shared<boost::asio::io_context>();
    std::thread server_thread([io_context] { runServer(io_context); });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Give the server a moment to start
    runClient(); // Run client
    
    io_context->stop(); // Signal the server to stop and cleanup
    server_thread.join();
	std::cout << '\n';

    return 0;
}
#pragma endregion //Trae