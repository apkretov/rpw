#if 1

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <array>
#include <string>
#include <iostream>
#include "../../stdafx.h"
using namespace boost::asio;
using namespace boost::asio::ip;

#pragma region Aliases
using byte_array = boost::asio::const_buffer;
using error_code = boost::system::error_code;
using io_service = boost::asio::io_service;
using resolver =   boost::asio::ip::tcp::resolver;
using std::array;
using std::cout;
using std::size_t;
using std::string;
#pragma endregion

io_service ioservice;
resolver resolv{ioservice};
tcp::socket tcp_socket{ioservice};
array<char, 4096> bytes;

/* read_handler() is called when one or more bytes have been received and copied to bytes. The parameter
bytes_transferred of type std::size_t contains the number of bytes that have been received. As usual, the
handler should check first ec whether the asynchronous operation was completed successfully. Only if this is the
case is data written to standard output. 
Please note that read_handler() calls async_read_some() again after data has been written to std::cout.
This is required because you can’t be sure that the entire homepage was downloaded and copied into bytes in
a single asynchronous operation. The repeated calls to async_read_some() followed by the repeated calls to
read_handler() only end when the connection is closed, which happens when the web server has sent the en-
tire homepage. Then read_handler() reports an error in ec. At this point, no further data is written to std::
cout and async_read() is not called on the socket. Because there are no pending asynchronous operations, the
program exits. */
void read_handler(const error_code &ec,	size_t bytes_transferred) { // Called when the data is received.
#pragma region MINE
	cout << "666\n";
	cout << AS_KV((!ec)) << '\n';
	cout << "Error Code: " << ec.value() << "\n";
	cout << "Error Message: " << ec.message() << "\n";
#pragma endregion //MINE
	if (!ec) {
		cout << AS_KV((!ec)) << '\n'; //MINE
		cout << "777\n"; //MINE
		cout.write(bytes.data(), bytes_transferred); // The array bytes is used to store data received.
		cout << "888\n"; //MINE
		tcp_socket.async_read_some(buffer(bytes), read_handler);
		cout << "999\n"; //MINE
	}
}

/* The call to async_connect() is followed by a call to the handler connect_handler(). Again ec is checked
first to find out whether a connection could be established. If so, async_read_some() is called on the socket. 
With this call, reading data begins. Data being received is stored in the array bytes, which is passed as a first
parameter to async_read_some(). */
void connect_handler(const error_code &ec) { // Called when the connection is established.
	cout << "555\n"; //MINE
	if (!ec) {
		string r = "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
		write(tcp_socket, buffer(r)); // tcp_socket is accessed to send a HTTP request and start receiving data.
		tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
}

/* When the name has been resolved, resolve_handler() is called. The handler first checks whether the name
resolution has been successful. In this case ec is 0. Only then is the socket accessed to establish a connection.
The address of the server to connect to is provided by the second parameter, which is of type boost::asio::
ip::tcp::resolver::iterator. This parameter is the result of the name resolution. */
void resolve_handler(const error_code &ec, resolver::iterator it) { // Used for name resolution.
	cout << "444\n"; //MINE
	if (!ec)
		tcp_socket.async_connect(*it, connect_handler); // The iterator it, which points to an endpoint resolved from the name, 
}														// is used with tcp_socket to establish a connection.

/* Because data can only be received after a connection has been established, 
and because a connection can only be established after the name has been resolved, 
the various asynchronous operations are started in handlers.
Since all operations are asynchronous, handlers are passed to the respective functions. */
int main() {
	print_file_line();

	resolver::query q{"theboostcpplibraries.com", "80"	}; // q represents a query for the name resolver.
	cout << "111\n"; //MINE
	resolv.async_resolve(q, resolve_handler); // By passing q to async_resolve(), an asynchronous operation is started to resolve the name.
	cout << "222\n"; //MINE
	ioservice.run(); // After the asynchronous operation has been started, run() is called on the I/O service object to pass control to the operating system.
	cout << "333\n"; //MINE
}
#endif //1

/*
Dialog 1.

- Me:

When 666 is printed the second time in 'void read_handler(const error_code &ec, size_t bytes_transferred)' after 999, (!ec) is = 0. 
Why ? What ec is passed to 'void read_handler(const error_code &ec, size_t bytes_transferred)' ?


- Trae:

Let me explain what's happening in this asynchronous networking code:

1. The second time `read_handler` is called, `(!ec) = 0` means that `ec` contains an error.This is actually expected behavior because :

- The first call to `read_handler` successfully reads the HTTP 301 response
- After printing "999", the code calls `async_read_some` again to try to read more data
- However, the server has already closed the connection after sending the complete HTTP 301 response
- Therefore, the second read attempt fails with an error code indicating the connection was closed

2. In this case, the error code passed to `read_handler` is likely `boost::asio::error::eof` or `boost::asio::error::connection_reset`, 
indicating that the remote server closed the connection.

To verify this, we can modify the code to print the actual error code and message:

```cpp:c : \_\rpw\C++\Examples\The Boost C++ Libraries\The Boost C++ Libraries\Example 32.5.cpp
void read_handler(const error_code & ec, size_t bytes_transferred) {
	cout << "666\n";
	cout << "Error Code: " << ec.value() << "\n";
	cout << "Error Message: " << ec.message() << "\n";
	cout << AS_KV((!ec)) << '\n';
	if (!ec) {
		// ... rest of the function remains the same ...
	}
}
```

This is normal behavior for HTTP / 1.1 connections where the server typically closes the connection after sending the complete response
(especially for simple requests like this one).If you need to make multiple requests, you would need to establish a new connection 
for each request or implement keep - alive functionality.


- Me:

Yes,
Error Code : 2
Error Message : End of file


- Trae:

Yes, as we can see from the output, when the second `read_handler` is called, we get :
- Error Code : 2
- Error Message : "End of file"

This confirms what I explained earlier. The error code 2 (`boost::asio::error::eof`) indicates that we've reached the end of the connection because:

	1. The server sent the complete HTTP 301 response
	2. Then the server closed the connection(which is normal HTTP / 1.1 behavior)
	3. When our code tried to read more data with the second `async_read_some`, it encountered EOF because 
	there was no more data to read on the closed connection

	This is not actually an error condition that needs to be handled as a failure - it's a normal part of HTTP connection lifecycle. 
	If you needed to continue communication with the server, you would need to:
	1. Either establish a new connection
	2. Or modify the HTTP request to include `Connection: keep - alive` header and handle persistent connections
*/

/*
Dialog 2.

- Me:

When the name has been resolved, resolve_handler() is called. The handler first checks whether the name resolution has been successful. In this case ec is 0. Only then is the socket accessed to establish a connection.
1. What name resolution is that?
2. What names does it resolve?
3. What is the result of that resolution?


- Trae:

Let me explain the name resolution process in this code:

1. * *What name resolution is that ? **
-This is DNS(Domain Name System) resolution
- The resolver is trying to convert a domain name into IP address(es) and port information that can be used to establish a TCP connection
- In the code, this is handled by `boost: : asio::ip::tcp::resolver`

2. * *What names does it resolve ? **
-It resolves the domain name "theboostcpplibraries.com" on port "80"
- This is specified in the resolver query :
```cpp:c : \_\rpw\C++\Examples\The Boost C++ Libraries\The Boost C++ Libraries\Example 32.5.cpp
resolver::query q{"theboostcpplibraries.com", "80"};
```

3. * *What is the result of that resolution ? **
-The resolution returns an iterator(`resolver::iterator it`) that contains one or more endpoints
	- Each endpoint includes :
-The resolved IP address of theboostcpplibraries.com
- The port number(80)
- The code uses the first endpoint from the iterator to establish the TCP connection :
```cpp:c : \_\rpw\C++\Examples\The Boost C++ Libraries\The Boost C++ Libraries\Example 32.5.cpp
tcp_socket.async_connect(*it, connect_handler);
```
- The `*it` dereferences the iterator to get the first endpoint, which is then used to establish the actual TCP connection

This resolution is necessary because TCP / IP networks operate on IP addresses, not domain names.The DNS resolution converts the human - readable domain name into the actual IP address needed for network communication.


- Me:

The resolution returns an iterator(resolver::iterator it) that contains one or more endpoints.
What is an endpoint?


- Trae: 

	An endpoint in networking context is a combination of :

1. * *IP Address * *: The resolved network address
2. * *Port Number * *: The specific port for the service

In this code, the endpoint is represented by `boost: : asio::ip::tcp::endpoint` which contains :
-The IP address resolved from "theboostcpplibraries.com"
- Port 80 (specified in the query)

The iterator can contain multiple endpoints because :
-A single domain name might resolve to multiple IP addresses(for load balancing or redundancy)
- The same service might be available on both IPv4 and IPv6 addresses

When the code does `*it` in the resolve handler :
```cpp:c : \_\rpw\C++\Examples\The Boost C++ Libraries\The Boost C++ Libraries\Example 32.5.cpp
tcp_socket.async_connect(*it, connect_handler);
```
It's using the first endpoint from this list to establish the TCP connection. If the connection fails, you could potentially try the next endpoint in the iterator (though this example doesn't implement that fallback behavior).


- Me:

Show boost::asio::ip::tcp::endpoint inside ?


- Trae:

	Let me show you the key components of a `boost: : asio::ip::tcp::endpoint`. An endpoint is a class that combines :

	```cpp
	namespace boost {
	namespace asio {
		namespace ip {
			namespace tcp {

				class endpoint {
				public:
					// Constructors
					endpoint(); // Default constructor
					endpoint(const tcp::v4(), unsigned short port_num); // IPv4 endpoint
					endpoint(const tcp::v6(), unsigned short port_num); // IPv6 endpoint
					endpoint(const address &addr, unsigned short port_num); // From address and port

					// Key Methods
					address address() const; // Get the IP address
					unsigned short port() const; // Get the port number
					void port(unsigned short port_num); // Set the port
					void address(const address &addr); // Set the address

					// Protocol-specific methods
					protocol_type protocol() const; // Get the associated protocol type
				};

			}
		}
	}
} // namespaces
```

This is why in your code, when the resolver returns endpoints, each endpoint contains both the resolved IP address and the port number(80) that were specified in the query.The socket can then use this complete information to establish the connection.

For example, an endpoint might represent :
-IPv4 : "192.168.1.1:80"
- IPv6 : "[2001:db8::1]:80"
*/