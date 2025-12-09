#pragma region MINE
#pragma once

#include <future>
#include <unordered_map>
#include <mutex>
#include <queue>
#include <string>
using namespace std;

using payload_type = string; // The data payload, can be any type. We'll use string for this example.

struct data_packet { // Represents a packet of data arriving from a connection
	int id;
	payload_type payload;
};

struct outgoing_packet { // Represents a packet of data to be sent out
	payload_type payload;
	promise<bool> promise; // Promise to signal successful sending
};

class connection { // A mock connection class
public:
	connection();
	connection(const connection&) = delete;
	connection& operator=(const connection&) = delete;
	connection(connection&& other) noexcept;
	connection& operator=(connection&& other) noexcept;

	bool has_incoming_data(); // --- Methods for the processing loop ---
	data_packet incoming();
	promise<payload_type>& get_promise(int id);
	bool has_outgoing_data();
	outgoing_packet top_of_outgoing_queue();
	void send(const payload_type& payload) const;

	future<bool> post_outgoing_data(payload_type data); // --- Methods for client simulation ---
	void simulate_incoming_data(data_packet packet);
	future<payload_type> wait_for_payload(int id);
private:
	queue<data_packet> incoming_queue;
	mutex incoming_mutex;
	unordered_map<int, promise<payload_type>> incoming_promises; // See Comment 1 below.

	queue<outgoing_packet> outgoing_queue;
	mutex outgoing_mutex;
};

/*
Comment 1.

Why is there no map for outgoing promises? I see the incoming and outgoing queues and two mutexes: one for incoming and
  one for outgoing. However, there is only a map for incoming promises. Why doesn't this connection class have a map for
  outgoing promises?

✦ The difference in design comes down to how the promises are used and correlated with the data they represent.

   * For Incoming Data: The incoming_promises map is needed to handle asynchronous requests. A client thread can say, "I am
	 interested in the payload for message id 123," by calling wait_for_payload(123). This happens before the data packet
	 with id 123 has necessarily arrived. The map stores the promise associated with this request, using the id as a key.
	 When the connection's processing loop eventually receives the packet with id 123, it uses the map to look up the
	 correct promise and fulfill it with the payload. The map is essential for correlating the later-arriving data with the
	 earlier request.

   * For Outgoing Data: The promise is bundled directly with the data in the outgoing_packet struct. When a client calls
	 post_outgoing_data, the connection class creates a promise, bundles it with the payload into an outgoing_packet, and
	 puts the whole thing on the outgoing_queue. The future from that promise is immediately returned to the client. The
	 sending part of the connection simply works through the queue; when it successfully sends a packet, it fulfills the
	 promise that is right there inside the packet it just processed. There's no need for a separate map because the promise
	 never gets separated from the data it corresponds to.
*/
#pragma endregion //MINE
