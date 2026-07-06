#pragma once

#pragma region MINE

#include <mutex>

struct connection_info { 
	int id; 
};

struct data_packet { 
	int id; 
};

struct connection_handle {
	void send_data(data_packet const& data) { std::print("thread {}: sending data\n", std::this_thread::get_id()); }
	
	data_packet receive_data() {
		std::print("thread {}: receiving data\n", std::this_thread::get_id());
		return data_packet();
	}
};

struct connection_manager {
	static connection_handle open(connection_info const& info) {
		std::print("thread {}: opening connection\n", std::this_thread::get_id());
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
		std::print("thread {}: open_connection() called\n", std::this_thread::get_id()); //MINE
		connection = connection_manager::open(connection_details);
	}
public:
	X(connection_info const& connection_details_) : connection_details(connection_details_) {}

	void send_data(data_packet const& data) {
		std::print("thread {}: send_data() called\n", std::this_thread::get_id()); //MINE
		std::call_once(connection_init_flag, &X::open_connection, this);
		connection.send_data(data);
	}

	data_packet receive_data() {
		std::print("thread {}: receive_data() called\n", std::this_thread::get_id()); //MINE
		std::call_once(connection_init_flag, &X::open_connection, this);
		return connection.receive_data();
	}
};
