#pragma once

#include <boost/asio.hpp>
#include "GumballMachine.h"
#include "SocketHandler.h"

#pragma region Trae
class GumballMachineServer {
	boost::asio::io_context &io_context_;
	boost::asio::ip::tcp::acceptor acceptor_;
	std::shared_ptr<GumballMachine> machine_;

	void handleRequest(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
		try {
			std::vector<char> buffer(1024);
			boost::system::error_code ec;
			size_t len = socket->read_some(boost::asio::buffer(buffer), ec);

			if (ec) {
				return;
			}

			std::string request(buffer.data(), len);
			std::string response;

			if (request == "getAllInfo\n") {
				response = machine_->getLocation() + "\n" +
					std::to_string(machine_->getCount()) + "\n" +
					machine_->getStateString() + "\n";
			}

			boost::asio::write(*socket, boost::asio::buffer(response), ec);
		}
		catch (const std::exception &) {
			// Handle error
		}
	}

public:
	GumballMachineServer(boost::asio::io_context &io_context, unsigned short port, std::shared_ptr<GumballMachine> machine)
		: io_context_(io_context)
		, acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
		, machine_(machine) {
		accept();
	}

private:
	void accept() {
		auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
		acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code &error) {
			if (!error) {
				handleRequest(socket);
			}
			accept();
			});
	}
};
#pragma endregion //Trae