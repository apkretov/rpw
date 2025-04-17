#pragma once

#include <boost/asio.hpp>
#include <string>
#include <vector>

class SocketHandler {
private:
#pragma region aliases
    using socket =     boost::asio::ip::tcp::socket;
    using char_vec =   std::vector<char>;
    using string =     std::string;
#pragma endregion //aliases
    socket& socket_;
public:
    explicit SocketHandler(socket& socket) : socket_(socket) {}

    string sendAndReceive(const string& message) const {
        uint32_t size = static_cast<uint32_t>(message.size()); // Send with size prefix
        boost::asio::write(socket_, boost::asio::buffer(&size, sizeof(size)));
        boost::asio::write(socket_, boost::asio::buffer(message));

        uint32_t response_size; // Read size first
        boost::asio::read(socket_, boost::asio::buffer(&response_size, sizeof(response_size)));

        char_vec data(response_size); // Then read exact amount of data
        boost::asio::read(socket_, boost::asio::buffer(data));

        return string(data.begin(), data.end());
    }
};