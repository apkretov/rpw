#pragma once

#pragma region MINE

#include <iostream>
#include <mutex>

struct connection_info {};
struct data_packet {};

struct connection_handle {
	void send_data(data_packet const& data) { std::cout << "sending data\n"; }
	
	data_packet receive_data() {
		std::cout << "receiving data\n";
		return data_packet();
	}
};

struct connection_manager {
	static connection_handle open(connection_info const& info) {
		std::cout << "opening connection\n";
		return connection_handle();
	}
};
#pragma endregion //MINE

class X { // Situation 1: // In this class, initialization is done either by the first call to send_data() or the first call to receive_data(). The `this` pointer is passed as an additional argument to std::call_once() to allow it to call the `open_connection` member function.
private:
	connection_info connection_details;
	connection_handle connection;
	std::once_flag connection_init_flag;
	void open_connection() {
		std::cout << "thread " << std::this_thread::get_id() << ": open_connection() called\n"; //MINE
		connection = connection_manager::open(connection_details);
	}
public:
	X(connection_info const& connection_details_) : connection_details(connection_details_) {}

	void send_data(data_packet const& data) {
		std::call_once(connection_init_flag, &X::open_connection, this);
		connection.send_data(data);
	}

	data_packet receive_data() {
		std::call_once(connection_init_flag, &X::open_connection, this);
		return connection.receive_data();
	}
};
