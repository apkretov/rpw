#ifdef MINE

#include <print>
#include <thread>
#include <vector>
#include "../../stdafx.h"
#include "Listing 3.12.h"

#undef	SITUATION_2

#ifdef SITUATION_2
class copyable_X { // Situation 2: std::once_flag instances can't be copied or moved. This means that if you use one as a class member, the compiler will not generate a copy constructor or copy-assignment operator for your class. If you need your class to be copyable, you have to explicitly define them.
private:
	connection_info connection_details;
	connection_handle connection;
	std::once_flag connection_init_flag;
	void open_connection() { connection = connection_manager::open(connection_details); }
public:
	explicit copyable_X(connection_info const& connection_details_) : connection_details(connection_details_) {}
	copyable_X(const copyable_X& other) : connection_details(other.connection_details) { std::print("Copy constructor for copyable_X called.\n"); } // We can explicitly define a copy constructor. The new object will have its own std::once_flag in its default (un-called) state. The connection itself is not copied; it will be initialized on first use in the new object.
	copyable_X& operator=(const copyable_X&) = delete; // std::once_flag is not copy-assignable. This means our class cannot be copy-assignable in any meaningful way that also handles the flag. We explicitly delete the copy-assignment operator to make this clear.

	void send_data(data_packet const& data) {
		std::call_once(connection_init_flag, &copyable_X::open_connection, this);
		connection.send_data(data);
	}

	data_packet receive_data() {
		call_once(connection_init_flag, &copyable_X::open_connection, this);
		return connection.receive_data();
	}
};
#endif //SITUATION_2

void use_x_in_thread(X& x) { x.send_data(data_packet{}); }

int main() {
	print_file_line();

	std::print("--- Situation 1: Initialization with std::call_once --- \n");
	connection_info details;
	X x(details);

	x.send_data(data_packet{}); // The connection is initialized only on the first call.
	x.receive_data();

	std::print("\n--- Situation 1 (multithreaded): Lazy initialization is thread-safe --- \n");
	X x_threaded(details);
	std::vector<std::jthread> threads;
	for (int i = 0; i < 3; ++i) 
		threads.emplace_back(use_x_in_thread, std::ref(x_threaded));
	for (auto& t : threads) 
		t.join();
	std::print("All threads finished. open_connection() was called only once.\n");

#ifdef SITUATION_2
	std::print("\n--- Situation 2: Handling non-copyable std::once_flag --- \n");

	// X x2 = x; // This line would cause a compilation error. Class X with a std::once_flag member is not copyable by default.

	copyable_X cx1(details);
	std::print("Created cx1. Initializing its connection.\n");
	cx1.send_data(data_packet{});

	std::print("\nCreating cx2 as a copy of cx1.\n");
	copyable_X cx2 = cx1; // Calls the user-defined copy constructor.

	std::print("cx2 is a new object with its own uninitialized connection.\n");
	std::print("Initializing connection for cx2.\n");
	cx2.send_data(data_packet{}); // The connection for cx2 is initialized here.

	// copyable_X cx3(details);
	// cx3 = cx1; // This would cause a compilation error because the assignment operator is deleted.
#endif // SITUATION_2

	return 0;
}
#endif // MINE
