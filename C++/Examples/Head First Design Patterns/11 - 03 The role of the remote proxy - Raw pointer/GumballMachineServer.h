#pragma once

#include <boost/asio.hpp>
#include "GumballMachine.h"
#include "SocketHandler.h"

#pragma region Trae
/* This server implementation:
- Uses asynchronous I/O for better performance
- Handles multiple clients
- Provides remote access to gumball machine state
- Implements part of the Proxy pattern by serving as the remote object
The server works alongside the GumballMachineProxy to enable remote monitoring of the gumball machine's state. */
class GumballMachineServer {
#pragma region Aliases									// 1. The class aliases:
    using io_context =	boost::asio::io_context;		// Manages I/O operations
    using acceptor =	boost::asio::ip::tcp::acceptor;	// Accepts incoming TCP connections
    using endpoint =	boost::asio::ip::tcp::endpoint;	// Represents network address and port
    using socket =		boost::asio::ip::tcp::socket;	// Handles TCP socket communications
    using error_code =	boost::system::error_code;
	using char_vec =	std::vector<char>;	
	using exception =	std::exception;
    using socket_ptr =	std::shared_ptr<socket>;
    using string =		std::string;
#pragma endregion //Aliases
public:
	GumballMachineServer(io_context& context, unsigned short port, const GumballMachine &machine) // 2. The constructor starts accepting connections.
        : context(context)
        , acceptor_(context, endpoint(boost::asio::ip::tcp::v4(), port))
        , machine(machine) 
	{ accept(); } // Starts accepting connections.
private:
    io_context& context;
    acceptor acceptor_;
    const GumballMachine &machine;

	/* 3. Request Handling:
	- Reads client request from socket
	- Processes "getAllInfo" command, which returns:
		- Machine location
		- Gumball count
		- Current state
	- Sends response back to client
	- Includes error handling */
    void handleRequest(socket_ptr socket_ptr_) {
        try {
			char_vec buffer(1024);
            error_code ec;
            size_t len = socket_ptr_->read_some(boost::asio::buffer(buffer), ec);
            if (ec)
                return;
            string response;
            if (string request(buffer.data(), len); request == "getAllInfo\n")
				response = std::format("{}\n{}\n{}\n", machine.getLocation(), machine.getCount(), machine.getStateString());
            boost::asio::write(*socket_ptr_, boost::asio::buffer(response), ec);
        }
        catch (const exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

	/* 4. Connection Acceptance:
	- Creates new socket for each connection
	- Uses asynchronous acceptance (non-blocking)
	- Handles incoming connections in a callback
	- Recursively calls itself to continue accepting connections */
    void accept() {
        auto socket_ptr_ = std::make_shared<socket>(context);
        acceptor_.async_accept(*socket_ptr_, [this, socket_ptr_](const error_code& error) {
            if (!error)
                handleRequest(socket_ptr_);
            accept();
        });
    }
};
#pragma endregion //Trae