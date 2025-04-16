#pragma once

#include <boost/asio.hpp>
#include <string>

class SocketHandler {
    boost::asio::ip::tcp::socket& socket_;
public:
    explicit SocketHandler(boost::asio::ip::tcp::socket& socket) : socket_(socket) {}

    std::string sendAndReceive(const std::string& message) const {
        uint32_t size = static_cast<uint32_t>(message.size()); // Send with size prefix
        boost::asio::write(socket_, boost::asio::buffer(&size, sizeof(size)));
        boost::asio::write(socket_, boost::asio::buffer(message));

        uint32_t response_size; // Read size first
        boost::asio::read(socket_, boost::asio::buffer(&response_size, sizeof(response_size)));

        std::vector<char> data(response_size); // Then read exact amount of data
        boost::asio::read(socket_, boost::asio::buffer(data));

        return std::string(data.begin(), data.end());
    }
};