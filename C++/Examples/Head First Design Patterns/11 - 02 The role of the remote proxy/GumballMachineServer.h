#pragma once

#include <boost/asio.hpp>
#include "GumballMachine.h"
#include "SocketHandler.h"

#pragma region Trae
class GumballMachineServer {
#pragma region aliases
    using io_context =         boost::asio::io_context;
    using acceptor =           boost::asio::ip::tcp::acceptor;
    using endpoint =           boost::asio::ip::tcp::endpoint;
    using socket =             boost::asio::ip::tcp::socket;
    using error_code =         boost::system::error_code;
    using char_vec =           std::vector<char>;
    using GumballMachine_ptr = std::shared_ptr<GumballMachine>;
    using socket_ptr =         std::shared_ptr<socket>;
    using string =             std::string;
#pragma endregion //aliases
    io_context& io_context_;
    acceptor acceptor_;
    GumballMachine_ptr machine_;

    void handleRequest(socket_ptr socket_) {
        try {
            char_vec buffer(1024);
            error_code ec;
            size_t len = socket_->read_some(boost::asio::buffer(buffer), ec);

            if (ec)
                return;

            string request(buffer.data(), len);
            string response;

            if (request == "getAllInfo\n") {
                response = machine_->getLocation() + "\n" +
                    std::to_string(machine_->getCount()) + "\n" +
                    machine_->getStateString() + "\n";
            }

            boost::asio::write(*socket_, boost::asio::buffer(response), ec);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    void accept() {
        auto socket_ = std::make_shared<socket>(io_context_);
        acceptor_.async_accept(*socket_, [this, socket_](const error_code& error) {
            if (!error)
                handleRequest(socket_);
            accept();
        });
    }
public:
    GumballMachineServer(io_context& io_context, unsigned short port, GumballMachine_ptr machine)
        : io_context_(io_context)
        , acceptor_(io_context, endpoint(boost::asio::ip::tcp::v4(), port))
        , machine_(machine) {
        accept();
    }
};
#pragma endregion //Trae