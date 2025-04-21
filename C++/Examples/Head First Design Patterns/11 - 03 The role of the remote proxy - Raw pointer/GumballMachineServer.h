#pragma once

#include <boost/asio.hpp>
#include "GumballMachine.h"

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
	
	/* - Me: Unlike std::array, this should be std::vector, shouldn't it?
	
	- Trae:
	Yes, using std::vector is better than std::array in this case for several reasons:
	1. Dynamic Sizing : While we're using a fixed size of 1024 bytes here, using std::vector gives us flexibility if we need to change 
	the buffer size later or make it dynamic based on message sizes.
	2. Stack vs Heap : With std::vector , the buffer is allocated on the heap, which is safer for larger sizes. 
	A 1024-byte std::array would be allocated on the stack, which:
	   - Could cause stack overflow with multiple concurrent connections
	   - Is less efficient for larger sizes
	   - Could be problematic in embedded systems or environments with limited stack space
	3. ASIO Compatibility : Boost.ASIO works well with both std::vector and std::array , but std::vector is more commonly used in ASIO examples and documentation, especially for receive buffers.
	So yes, the current implementation using std::vector (as char_vec ) is the better choice for this network buffer.

	- Me: Who would change the size: me in the code or a boost::asio function?

	- Trae: Boost.ASIO itself won't automatically resize the buffer - that would be your responsibility if needed. */
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
			/* - Me: What will happen, if my chosen size won't suffice? A run_time exception?

			- Trae:
			When using read_some with a buffer that's too small for the incoming data, no exception will be thrown. Instead, read_some will:
			1. Read as much data as it can fit into the buffer (up to buffer.size())
			2. Return the number of bytes actually read
			3. Leave the remaining data in the socket's receive buffer

			So in this code, if a 2000-byte message arrives:
			- Only the first 1024 bytes will be read
			- len will be 1024
			- The remaining 976 bytes will stay in the socket buffer
			- No exception or error will occur
			
			This is actually a potential issue in the current code because we assume the entire message fits in one read. 
			For a more robust implementation, you'd need to:
			1. Either ensure your protocol never exceeds the buffer size
			2. Or implement message framing with multiple reads to handle larger messages
			*/
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