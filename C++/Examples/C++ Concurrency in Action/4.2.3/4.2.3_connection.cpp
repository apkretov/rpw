#pragma region MINE

#include <chrono>
#include <print>
#include <thread>
#include "4.2.3_connection.h"
using namespace std;

connection::connection() = default;

connection::connection(connection&& other) noexcept {
	if (this != &other) {
		scoped_lock lock(incoming_mutex, outgoing_mutex, other.incoming_mutex, other.outgoing_mutex);
		incoming_queue = move(other.incoming_queue);
		incoming_promises = move(other.incoming_promises);
		outgoing_queue = move(other.outgoing_queue);
	}
}

connection& connection::operator=(connection&& other) noexcept {
	if (this != &other) {
		scoped_lock lock(incoming_mutex, outgoing_mutex, other.incoming_mutex, other.outgoing_mutex);
		incoming_queue = move(other.incoming_queue);
		incoming_promises = move(other.incoming_promises);
		outgoing_queue = move(other.outgoing_queue);
	}
	return *this;
}

bool connection::has_incoming_data() {
	lock_guard lock(incoming_mutex);
	return !incoming_queue.empty();
}

data_packet connection::incoming() {
	lock_guard lock(incoming_mutex);
	data_packet data = incoming_queue.front();
	incoming_queue.pop();
	return data;
}

promise<payload_type>& connection::get_promise(int id) {
	lock_guard lock(incoming_mutex);
	return incoming_promises[id];
}

bool connection::has_outgoing_data() {
	lock_guard lock(outgoing_mutex);
	return !outgoing_queue.empty();
}

outgoing_packet connection::top_of_outgoing_queue() {
	lock_guard lock(outgoing_mutex);
	outgoing_packet data = move(outgoing_queue.front());
	outgoing_queue.pop();
	return data;
}

void connection::send(const payload_type& payload) const {
	print("[Processor] Sending data: \"{}\"\n", payload);
	this_thread::sleep_for(chrono::milliseconds(100));
}

future<bool> connection::post_outgoing_data(payload_type data) {
	promise<bool> p;
	auto f = p.get_future();
	lock_guard lock(outgoing_mutex);
	outgoing_queue.push({move(data), move(p)});
	return f;
}

void connection::simulate_incoming_data(data_packet packet) {
	lock_guard lock(incoming_mutex);
	incoming_queue.push(packet);
}

future<payload_type> connection::wait_for_payload(int id) {
	lock_guard lock(incoming_mutex);
	return incoming_promises[id].get_future();
}
#pragma endregion //MINE

