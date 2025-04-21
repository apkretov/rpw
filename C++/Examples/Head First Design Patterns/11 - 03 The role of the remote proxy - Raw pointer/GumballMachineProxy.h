#pragma once

#include <boost/asio.hpp>
#include <optional>
#include <string>
#include <vector>
#include "GumballMachineI.h"
#include "SocketHandler.h"

#pragma region Trae
/* 1. Class Structure: implements IGumballMachine, acting as a remote proxy that:
- Handles network communication
- Caches machine information
- Provides the same interface as the real gumball machine */
class GumballMachineProxy : public IGumballMachine {
#pragma region aliases
	using io_context =		boost::asio::io_context;
	using resolver =		boost::asio::ip::tcp::resolver;
	using socket =			boost::asio::ip::tcp::socket;
	using error_code =		boost::system::error_code;
	using system_error =	boost::system::system_error;
	using istringstream =	std::istringstream;
	using string =			std::string;
	using char_vec =		std::vector<char>;
#pragma endregion //aliases
	const io_context &context;
    mutable socket socket_;
    string host;
    unsigned short port;
    mutable SocketHandler handler;
public:
	/* 2. The constructor:
	- Takes IO context, host, and port
	- Establishes TCP connection to the server
	- Uses resolver to handle hostname resolution
	- Initializes socket connection */
    GumballMachineProxy(io_context& context, const string& host, unsigned short port) 
        : context(context)
        , socket_(context)
        , host(host)
        , port(port)
        , handler(socket_) 
	{
        resolver resolver(context);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::connect(socket_, endpoints);
    }
private:
	/* 3. Caching Mechanism:
	- Caches all machine information in one structure
	- Uses std::optional for lazy initialization 
	- Reduces network requests by batching data	*/
	struct MachineInfo {	// Maintain the connection between requests:
        string location;	// 1. Make a single network request to fetch all machine information at once
        int count;			// 2. Cache the results
        string state;		// 3. Return cached values for subsequent calls
    };						// 4. Reduce network overhead and connection issues
							// This prevents the error that was occurring because each method call was making a separate network request, and the connection was being reset between calls. By batching the requests into a single call, this issue is avoided.
    mutable std::optional<MachineInfo> cached_info;

	/* 4. Network Communication:
	- Sends "getAllInfo" request to server
	- Reads and parses response
	- Updates cache with received information
	- Handles network errors */
    void fetchInfo() const {
        try {
            string request = "getAllInfo\n";
            boost::asio::write(socket_, boost::asio::buffer(request));
            char_vec buffer(1024);
            error_code ec;
            size_t len = socket_.read_some(boost::asio::buffer(buffer), ec);
            if (ec)
                throw system_error(ec);

            string response(buffer.data(), len);
            istringstream iss(response);
            MachineInfo info;
            std::getline(iss, info.location);
            string count_str;
            std::getline(iss, count_str);
            info.count = std::stoi(count_str);
            std::getline(iss, info.state);
            cached_info = std::move(info);
        }
        catch (const system_error& e) {
            throw;
        }
    }
public:
    string getLocation() const override {
        if (!cached_info)
            fetchInfo();
        return cached_info->location;
    }

    int getCount() const override {
        if (!cached_info)
            fetchInfo();
        return cached_info->count;
    }

    string getStateString() const override {
        if (!cached_info)
            fetchInfo();
        return cached_info->state;
    }
};
#pragma endregion //Trae