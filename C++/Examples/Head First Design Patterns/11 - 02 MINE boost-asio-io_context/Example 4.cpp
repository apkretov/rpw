#ifndef MINE
/*
4. Simple TCP client: connect and read
This example connects to a server, reads a line, and closes. It shows how sockets are tied to io_context.
Key ideas:
tcp::resolver, tcp::socket are constructed with io.
All async operations (async_connect, async_write, async_read_some) post their completion handlers to io.
io.run() drives everything: when the OS says “connected”, “written”, “data ready”, Asio calls your lambdas.
You don’t manually “wait” anywhere; the event loop does it.
*/

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <array>
#include "../../stdafx.h"

static void start_read(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io) {
	auto buf = std::make_shared<std::array<char, 1024>>(); // Async read some bytes
	socket.async_read_some(boost::asio::buffer(*buf), [&, buf](const boost::system::error_code& ec, std::size_t n) {
		if (ec) {
			std::cerr << "Read error: " << ec.message() << "\n";
			io.stop();
			return;
		}

		std::cout << "Received " << n << " bytes:\n\n";
		std::cout.write(buf->data(), static_cast<std::streamsize>(n)); // Application payload from the peer (here: HTTP response text), not socket/Asio internals
		std::cout << "\n";
		io.stop();  // we’re done
	});
}

static void start_http_exchange(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io, const std::string& host) {
	auto request = std::make_shared<std::string>( // No space after \r\n — header lines must start with the field name (RFC 7230). Host must match the server you connected to.
		"GET / HTTP/1.1\r\n"
		"Host: " + host + "\r\n"
		"Connection: close\r\n"
		"\r\n"); // Keep the request alive until async_write finishes (buffer() only views the data; it does not copy it).
	boost::asio::async_write(socket, boost::asio::buffer(*request), [&, request](const boost::system::error_code& ec, std::size_t) {
		if (ec) {
			std::cerr << "Write error: " << ec.message() << "\n";
			io.stop();
			return;
		}
		start_read(socket, io);
	});
}

int main() {
	print_file_line();

	try {
		const std::string host = "google.com"; // Try "example.com" too; Host header stays in sync via start_http_exchange(..., host)
		boost::asio::io_context io;
		boost::asio::ip::tcp::resolver resolver(io); // Resolve host (e.g. example.com:80)
		auto endpoints = resolver.resolve(host, "80");
		boost::asio::ip::tcp::socket socket(io);

		boost::asio::async_connect(socket, endpoints, [&](const boost::system::error_code& ec, const boost::asio::ip::tcp::endpoint&) { // Async connect
			if (ec) {
				std::cerr << "Connect error: " << ec.message() << "\n";
				io.stop();  // stop the event loop
				return;
			}
			std::cout << "Connected\n\n";
			start_http_exchange(socket, io, host);
		});

		io.run(); // Run the event loop
		std::cout << "Finished\n";
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
#endif // MINE
