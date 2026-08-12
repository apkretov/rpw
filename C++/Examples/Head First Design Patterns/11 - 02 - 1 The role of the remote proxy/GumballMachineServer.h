#pragma once

#include <boost/asio.hpp>
#include <format>
#include "GumballMachine.h"
#include "GumballConstants.h"
#include "SocketHandler.h"

#pragma region Trae
class GumballMachineServer {
#pragma region Aliases
    using io_context =         boost::asio::io_context;
    using acceptor =           boost::asio::ip::tcp::acceptor;
    using endpoint =           boost::asio::ip::tcp::endpoint;
    using socket =             boost::asio::ip::tcp::socket;
    using error_code =         boost::system::error_code;
    using char_vec =           std::vector<char>;
    using GumballMachine_ptr = std::shared_ptr<GumballMachine>;
    using socket_ptr =         std::shared_ptr<socket>;
    using string =             std::string;
#pragma endregion //Aliases
    io_context& io_context_;
    acceptor acceptor_;
    GumballMachine_ptr machine_ptr_;

    void handleRequest(socket_ptr socket_) const {
        try {
            char_vec buffer(gumball_constants::kSocketBufferSize);
            error_code ec;
            size_t len = socket_->read_some(boost::asio::buffer(buffer), ec);

            if (ec)
                return;

            string request(buffer.data(), len);
            string response;
            if (request == gumball_constants::kGetAllInfoRequest)
                response = std::format("{}\n{}\n{}\n", machine_ptr_->getLocation(), machine_ptr_->getCount(), machine_ptr_->getStateString());
            boost::asio::write(*socket_, boost::asio::buffer(response), ec);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }

    void accept() {
        auto socket_ptr = std::make_shared<socket>(io_context_);
        acceptor_.async_accept(*socket_ptr, [this, socket_ptr](const error_code& error) {
            if (!error)
                handleRequest(socket_ptr);
            accept();
        });
    }
public:
    GumballMachineServer(io_context& io_context, unsigned short port__, GumballMachine_ptr machine_ptr)
        : io_context_(io_context)
        , acceptor_(io_context, endpoint(boost::asio::ip::tcp::v4(), port__))
        , machine_ptr_(machine_ptr) 
	{ accept(); }
};
#pragma endregion //Trae