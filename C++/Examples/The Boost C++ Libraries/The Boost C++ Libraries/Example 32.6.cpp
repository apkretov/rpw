#if 1

#define _CRT_SECURE_NO_WARNINGS

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>
#include <ctime>
#include "../../stdafx.h"

#pragma region Aliases
using namespace boost::asio;
using namespace boost::asio::ip;
using io_service =     boost::asio::io_service;
using endpoint =       boost::asio::ip::tcp::endpoint;
using error_code =     boost::system::error_code;
using tcp_acceptor =   boost::asio::ip::tcp::acceptor;
using std::cout;
using std::string;
using std::time;
using std::time_t;
#pragma endregion

io_service ioservice;
tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
tcp_acceptor acceptor{ioservice, tcp_endpoint};
tcp::socket tcp_socket{ioservice};
string data;

void write_handler(const error_code &ec, size_t bytes_transferred) {
    if (!ec)
        tcp_socket.shutdown(tcp::socket::shutdown_send);
}

void accept_handler(const error_code &ec) {
    if (!ec) {
        time_t now = time(nullptr);
        data = std::ctime(&now);
        async_write(tcp_socket, buffer(data), write_handler);
    }
}

int main() {
    print_file_line();

	cout << "The time server has started.\n";

    acceptor.listen();
    acceptor.async_accept(tcp_socket, accept_handler);
    ioservice.run();
}
#endif //1