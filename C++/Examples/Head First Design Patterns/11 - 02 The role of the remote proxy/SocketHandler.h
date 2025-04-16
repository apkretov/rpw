#pragma once
#include <boost/asio.hpp>
#include <string>

class SocketHandler {
    boost::asio::ip::tcp::socket& socket_;

public:
    explicit SocketHandler(boost::asio::ip::tcp::socket& socket) : socket_(socket) {}

    std::string sendAndReceive(const std::string& message) const {
        // Send with size prefix
        uint32_t size = static_cast<uint32_t>(message.size());
        boost::asio::write(socket_, boost::asio::buffer(&size, sizeof(size)));
        boost::asio::write(socket_, boost::asio::buffer(message));

        // Read size first
        uint32_t response_size;
        boost::asio::read(socket_, boost::asio::buffer(&response_size, sizeof(response_size)));

        // Then read exact amount of data
        std::vector<char> data(response_size);
        boost::asio::read(socket_, boost::asio::buffer(data));

        return std::string(data.begin(), data.end());
    }
};