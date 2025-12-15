#pragma region MINE

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <print>
#include <thread>
#include <vector>
#include "connection.h"
using namespace std;

#define INCOMING
#define OUTGOING

using connection_set = vector<connection>; // Define connection_set and iterators for process_connections
using connection_iterator = connection_set::iterator;

atomic<bool> global_done_flag(false); // A flag to control the main loop of the processing thread

static bool done(const connection_set&) { return global_done_flag.load(); }

#include "listing_4.10.h" // Include the original code from the listing. The file must be included here after the types declared above.

int main() {
	connection_set connections; // 1. Set up a collection with one connection
	connections.emplace_back();

	jthread processing_thread(process_connections, ref(connections)); // 2. Start the connection processing in a separate thread
	print("[Main] Started connection processing thread.\n");

#ifdef OUTGOING
	print("[Main] Client posting 'Hello World' message to be sent.\n"); // 3. Simulate a client interacting with the connection
	future<bool> send_future = connections[0].post_outgoing_data("Hello World");
#endif // OUTGOING

#ifdef INCOMING
	print("[Main] Client waiting for incoming data with ID 42.\n");
	future<payload_type> receive_future = connections[0].wait_for_payload(42);
#endif // INCOMING

	this_thread::sleep_for(chrono::milliseconds(250)); // 4. Simulate some other system component providing data for the connection
#ifdef INCOMING
	print("[Main] Simulating arrival of a packet with ID 42.\n");
	connections[0].simulate_incoming_data({42, "This is the response."});
#endif // INCOMING

	try { // 5. Wait on the futures to get the results
#ifdef OUTGOING
		bool sent_ok = send_future.get(); // See Comment 1 below.
		print("[Main] Client confirmed 'Hello World' was sent: {}\n", sent_ok);
#endif // OUTGOING

#ifdef INCOMING
		payload_type received_payload = receive_future.get();
		print("[Main] Client received payload for ID 42: \"{}\"\n", received_payload);
#endif // INCOMING
	}
	catch (const exception& e) {
		cerr << "An exception occurred: " << e.what() << endl;
	}

	print("[Main] Shutting down.\n"); // 6. Signal the processing thread to shut down and wait for it to finish
	global_done_flag = true;

	return 0;
}
/* 
Comment 1. 

sent_ok is equal to true because the process_connections function, running in a separate thread, explicitly sets the
promise<bool> associated with the outgoing data to true after processing it.

Here's a step-by-step explanation:

1. `connection::post_outgoing_data`: When connections[0].post_outgoing_data("Hello World") is called, it creates a
std::promise<bool> and obtains its associated std::future<bool>.This promise and the "Hello World" data are then
encapsulated in an outgoing_packet and pushed onto the outgoing_queue of the connection object. The future<bool> is
returned and assigned to send_future.

2. `process_connections` thread: The jthread processing_thread(process_connections, ref(connections)) runs the
process_connections function concurrently.This function continuously iterates through the connections.

3. Fulfilling the promise : Inside process_connections(specifically in listing_4.10.h), when an outgoing_packet is found
in the outgoing_queue(checked by connection->has_outgoing_data() at line ❺), the packet is retrieved from the queue
(connection->top_of_outgoing_queue()). The connection->send(data.payload) simulates the sending of data.Crucially, at
line ❻, data.promise.set_value(true); is called.This fulfills the std::promise<bool> that was created in
post_outgoing_data and passed along with the data.

4. `send_future.get()`: Back in main, when send_future.get() is called, it waits for the std::promise<bool> to be
fulfilled by the process_connections thread. Once data.promise.set_value(true) is executed, send_future.get()
retrieves this true value, and thus sent_ok becomes true.
*/
#pragma endregion //MINE