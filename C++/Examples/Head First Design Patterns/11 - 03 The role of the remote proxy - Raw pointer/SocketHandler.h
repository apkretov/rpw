#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>

class SocketHandler {
#pragma region Aliases
    using socket =     boost::asio::ip::tcp::socket;
    using string =     std::string;
    using char_vec =   std::vector<char>;
#pragma endregion //Aliases
    socket& socket__;
public:
    explicit SocketHandler(socket& socket_) : socket__(socket_) {}

    string sendAndReceive(const string& message) const {
        uint32_t size = static_cast<uint32_t>(message.size()); // Send with size prefix
        boost::asio::write(socket__, boost::asio::buffer(&size, sizeof(size)));
        boost::asio::write(socket__, boost::asio::buffer(message));

        uint32_t response_size; // Read size first
        boost::asio::read(socket__, boost::asio::buffer(&response_size, sizeof(response_size)));

        char_vec data(response_size); // Then read exact amount of data
        boost::asio::read(socket__, boost::asio::buffer(data));

        return string(data.begin(), data.end());
    }
};