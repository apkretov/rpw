#ifndef MINE

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// The following definitions are from Listing 3.12.h
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

// Situation 1:
// In this class, from Listing 3.12.h, initialization is done either by the
// first call to send_data() or the first call to receive_data(). The `this`
// pointer is passed as an additional argument to std::call_once() to allow it
// to call the `open_connection` member function.
class X {
private:
	connection_info connection_details;
	connection_handle connection;
	std::once_flag connection_init_flag;
	void open_connection() {
		std::cout << "thread " << std::this_thread::get_id()
			<< ": open_connection() called\n";
		connection = connection_manager::open(connection_details);
	}

public:
	X(connection_info const& connection_details_)
		: connection_details(connection_details_) {
	}

	void send_data(data_packet const& data) {
		std::call_once(connection_init_flag, &X::open_connection, this);
		connection.send_data(data);
	}
	data_packet receive_data() {
		std::call_once(connection_init_flag, &X::open_connection, this);
		return connection.receive_data();
	}
};

// Situation 2:
// std::once_flag instances can't be copied or moved. This means that if you
// use one as a class member, the compiler will not generate a copy
// constructor or copy-assignment operator for your class. If you need your
// class to be copyable, you have to explicitly define them.

class copyable_X {
private:
	connection_info connection_details;
	connection_handle connection;
	std::once_flag connection_init_flag;
	void open_connection() {
		connection = connection_manager::open(connection_details);
	}

public:
	copyable_X(connection_info const& connection_details_)
		: connection_details(connection_details_) {
	}

	// We can explicitly define a copy constructor. The new object will have
	// its own std::once_flag in its default (un-called) state. The connection
	// itself is not copied; it will be initialized on first use in the new
	// object.
	copyable_X(const copyable_X& other)
		: connection_details(other.connection_details) {
		std::cout << "Copy constructor for copyable_X called.\n";
	}

	// std::once_flag is not copy-assignable. This means our class cannot be
	// copy-assignable in any meaningful way that also handles the flag. We
	// explicitly delete the copy-assignment operator to make this clear.
	copyable_X& operator=(const copyable_X&) = delete;

	void send_data(data_packet const& data) {
		std::call_once(connection_init_flag, &copyable_X::open_connection, this);
		connection.send_data(data);
	}
	data_packet receive_data() {
		std::call_once(connection_init_flag, &copyable_X::open_connection, this);
		return connection.receive_data();
	}
};

void use_x_in_thread(X& x) { x.send_data(data_packet{}); }

int main() {
	std::cout << "--- Situation 1: Initialization with std::call_once --- ";
	connection_info details;
	X x(details);

	// The connection is initialized only on the first call.
	x.send_data(data_packet{});
	x.receive_data();

	std::cout << "\n--- Situation 1 (multithreaded): Lazy initialization is " "thread-safe --- ";
	X x_threaded(details);
	std::vector<std::thread> threads;
	for (int i = 0; i < 3; ++i) {
		threads.emplace_back(use_x_in_thread, std::ref(x_threaded));
	}
	for (auto& t : threads) {
		t.join();
	}
	std::cout << "All threads finished. open_connection() was called only once.\n";

	std::cout << "\n--- Situation 2: Handling non-copyable std::once_flag --- ";

	std::cout << "Class X with a std::once_flag member is not copyable by default.\n";
	// X x2 = x; // This line would cause a compilation error.

	copyable_X cx1(details);
	std::cout << "Created cx1. Initializing its connection.\n";
	cx1.send_data(data_packet{});

	std::cout << "\nCreating cx2 as a copy of cx1.\n";
	copyable_X cx2 = cx1; // Calls the user-defined copy constructor.

	std::cout << "cx2 is a new object with its own uninitialized connection.\n";
	std::cout << "Initializing connection for cx2.\n";
	cx2.send_data(data_packet{}); // The connection for cx2 is initialized here.

	// copyable_X cx3(details);
	// cx3 = cx1; // This would cause a compilation error because the assignment
	// operator is deleted.
	std::cout << "\ncopyable_X is not assignable, as operator= is deleted.\n";

	return 0;
}
#endif // MINE
