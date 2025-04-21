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
        , gumballMachine(machine) 
	{ accept(); } // Starts accepting connections.
private:
    io_context& context;
    acceptor acceptor_;
    const GumballMachine &gumballMachine;

	/* 3. Request Handling:
	- Reads client request from socket
	- Processes "getAllInfo" command, which returns:
		- Machine location
		- Gumball count
		- Current state
	- Sends response back to client
	- Includes error handling */
    void handleRequest(socket_ptr socketPtr) {
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

			/* -Me: Now, comment the same command vs. async_read_some here.

			- Trae:
			 read_some (current):
			 - Blocks the current thread until data arrives
			 - Simpler but less scalable
			 - Not ideal for server handling multiple clients

			 async_read_some (better for server):
			 - Non-blocking, returns immediately
			 - Better for handling multiple clients
			 - Consistent with server's async design pattern
			 - Would match our async_accept approach
			 socketPtr->async_read_some(boost::asio::buffer(buffer), [this, socketPtr](const error_code& ec, std::size_t len) {
				// Handle the read data here
			 });

			 In this server implementation, async_read_some would actually be more appropriate since we're already using async operations with 
			 async_accept. It would provide better scalability for handling multiple clients simultaneously.
			*/
			size_t len = socketPtr->read_some(boost::asio::buffer(buffer), ec);
            if (ec)
                return;
            
			string response;
            if (string request(buffer.data(), len); request == "getAllInfo\n")
				response = std::format("{}\n{}\n{}\n", gumballMachine.getLocation(), gumballMachine.getCount(), gumballMachine.getStateString());
            boost::asio::write(*socketPtr, boost::asio::buffer(response), ec);
        }
        catch (const exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

	/* 4. Connection Acceptance:
	- Creates new socket for each connection
	- Uses asynchronous acceptance (non-blocking)
	- Handles incoming connections in a callback
	- Recursively calls itself to continue accepting connections 
	
	- Me: I don't understand how this recursive loop ends...

	- Trae:
	The accept() call in the lambda function creates what appears to be an infinite recursion, but it's not actually recursive 
	in the traditional sense. Here's how it works:
	1. The async pattern creates an event loop, not a call stack.
	2. When accept() is called:
	   - It registers a callback with the IO service
	   - Returns immediately
	   - The lambda is executed later when a connection arrives
	   - The new accept() call just registers another callback
	3. The loop ends when:
	   - The server is shut down
	   - The io_context is stopped
	   - An unhandled error occurs
	It's more like setting up a repeating event handler than a recursive function. Each accept() call schedules the next one, 
	but they don't stack up in memory because they're handled asynchronously by the event loop.
	*/
    void accept() {
        auto socketPtr = std::make_shared<socket>(context);
        acceptor_.async_accept(*socketPtr, [this, socketPtr](const error_code& error) {
            if (!error)
                handleRequest(socketPtr);
            accept();
        });
    }
};
#pragma endregion //Trae