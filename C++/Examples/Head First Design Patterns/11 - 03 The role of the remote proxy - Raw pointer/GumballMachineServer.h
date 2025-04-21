#pragma once

#include <boost/asio.hpp>
#include <array>
#include "GumballMachine.h"
#include "SocketHandler.h"

#pragma region Trae
class GumballMachineServer {
#pragma region Aliases
    using io_context =         boost::asio::io_context;
    using acceptor =           boost::asio::ip::tcp::acceptor;
    using endpoint =           boost::asio::ip::tcp::endpoint;
    using socket =             boost::asio::ip::tcp::socket;
    using error_code =         boost::system::error_code;
    using char_arr =           std::array<char, 1024>;
    using socket_ptr =         std::shared_ptr<socket>;
    using string =             std::string;
#pragma endregion //Aliases
public:
    GumballMachineServer(io_context& context, unsigned short port, const GumballMachine &machine)
        : context(context)
        , acceptor_(context, endpoint(boost::asio::ip::tcp::v4(), port))
        , machine(machine) 
	{ accept(); }
private:
    io_context& context;
    acceptor acceptor_;
    const GumballMachine &machine;

    void handleRequest(socket_ptr socket_) {
        try {
            char_arr buffer;
            error_code ec;
            size_t len = socket_->read_some(boost::asio::buffer(buffer), ec);

            if (ec)
                return;

            string request(buffer.data(), len);
            string response;

            if (request == "getAllInfo\n") {
                response = machine.getLocation() + "\n" +
                    std::to_string(machine.getCount()) + "\n" +
                    machine.getStateString() + "\n";
            }

            boost::asio::write(*socket_, boost::asio::buffer(response), ec);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    void accept() {
        auto socket_ptr = std::make_shared<socket>(context);
        acceptor_.async_accept(*socket_ptr, [this, socket_ptr](const error_code& error) {
            if (!error)
                handleRequest(socket_ptr);
            accept();
        });
    }
};
#pragma endregion //Trae