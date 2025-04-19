#pragma once

#include <boost/asio.hpp>
#include <optional>
#include <string>
#include <vector>
#include "GumballMachineI.h"
#include "SocketHandler.h"

#pragma region Trae
class GumballMachineProxy : public IGumballMachine {
#pragma region aliases
	using io_context =		boost::asio::io_context;
	using resolver =		boost::asio::ip::tcp::resolver;
	using socket =			boost::asio::ip::tcp::socket;
	using error_code =		boost::system::error_code;
	using system_error =	boost::system::system_error;
	using string =			std::string;
#pragma endregion //aliases
	io_context &io_context_;
    mutable socket socket_;
    string host_;
    unsigned short port_;
    mutable SocketHandler handler_;
public:
    GumballMachineProxy(io_context& io_context, const string& host, unsigned short port)
        : io_context_(io_context)
        , socket_(io_context)
        , host_(host)
        , port_(port)
        , handler_(socket_) 
	{
        resolver resolver(io_context_);
        auto endpoints = resolver.resolve(host_, std::to_string(port_));
        boost::asio::connect(socket_, endpoints);
    }

	struct MachineInfo {	// Maintain the connection between requests:
        string location;	// 1. Make a single network request to fetch all machine information at once
        int count;			// 2. Cache the results
        string state;		// 3. Return cached values for subsequent calls
    };						// 4. Reduce network overhead and connection issues
							// This prevents the error that was occurring because each method call was making a separate network request, and the connection was being reset between calls.By batching the requests into a single call, this issue is avoided.
    mutable std::optional<MachineInfo> cached_info_;

    void fetchInfo() const {
        try {
            string request = "getAllInfo\n";
            boost::asio::write(socket_, boost::asio::buffer(request));
            
            std::vector<char> buffer(1024);
            error_code ec;
            size_t len = socket_.read_some(boost::asio::buffer(buffer), ec);
            
            if (ec)
                throw system_error(ec);

            string response(buffer.data(), len);
            std::istringstream iss(response);
            MachineInfo info;
            std::getline(iss, info.location);
            string count_str;
            std::getline(iss, count_str);
            info.count = std::stoi(count_str);
            std::getline(iss, info.state);
            
            cached_info_ = info;
        }
        catch (const system_error& e) {
            throw;
        }
    }

    string getLocation() const override {
        if (!cached_info_)
            fetchInfo();
        return cached_info_->location;
    }

    int getCount() const override {
        if (!cached_info_)
            fetchInfo();
        return cached_info_->count;
    }

    string getStateString() const override {
        if (!cached_info_)
            fetchInfo();
        return cached_info_->state;
    }
};
#pragma endregion //Trae