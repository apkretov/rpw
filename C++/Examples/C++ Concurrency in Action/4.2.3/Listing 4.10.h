#pragma once

#include <future>

void process_connections(connection_set& connections) {
	while (!done(connections)) { // ❶ // See Comment 1 below.
		for (connection_iterator connection = connections.begin(), end = connections.end(); connection != end; ++connection) { // ❷ // See Comment 2 below.
			if (connection->has_incoming_data()) {		// ❸ // See Comment 3 below.
				data_packet data = connection->incoming();
				std::promise<payload_type>& p = connection->get_promise(data.id);  // ❹
				p.set_value(data.payload);
			}
			if (connection->has_outgoing_data()) {		// ❺
				outgoing_packet data = connection->top_of_outgoing_queue();
				connection->send(data.payload);
				data.promise.set_value(true);			// ❻
			}
		}
	}
}

#pragma region MINE
/*
Comment 1.

Also instead of the busy waiting (while (!done(connections)) in Listing 4.10.h), would condition variables be more
  performant?

✦ Yes, using condition variables would generally be more performant than busy waiting (while (!done(connections))) in
  Listing 4.10.h.

  Busy waiting consumes CPU cycles continuously by repeatedly checking a condition, even when it's not likely to change.
  This can lead to inefficient resource usage, increased power consumption, and potentially slower performance for other
  tasks on the system.

  Condition variables, in contrast, allow threads to efficiently wait for a specific condition to become true without
  actively consuming CPU time. A thread waiting on a condition variable will block (go to sleep) until another thread
  explicitly notifies it that the condition might have changed. This approach is much more efficient as it releases the CPU
  for other processes during idle periods, leading to better overall system performance and responsiveness.

  To implement this, you would:
   1. Introduce std::mutex and std::condition_variable members to the connection class (or globally if processing all
	  connections together).
   2. Have the processing threads wait() on the condition variable when their respective queues (incoming or outgoing) are
	  empty.
   3. Have the post_outgoing_data and simulate_incoming_data methods notify_one() or notify_all() on the appropriate
	  condition variable when they add data to their queues.
*/

/*
Comment 2.

First Version :	 for (connection_iterator connection = connections.begin(), end = connections.end(); connection != end; ++connection) { ...
Second Version : for (auto connection = connections.begin(); connection != connections.end(); ++connection) { ...

The first loop version stores the container's `end` iterator once before the loop, avoiding repeated calls to `connections.end()` in each iteration. This can improve performance, especially for containers where `end()` is expensive to compute. The second version calls `connections.end()` every iteration, which may be less efficient.

For `std::vector`, the difference is usually negligible because `end()` is a simple, constant - time pointer retrieval.Still, the first version has a minor advantage by avoiding repeated calls.

However, iterator invalidation is a key concern.If the container changes during iteration(e.g., via insertion causing reallocation in a `std::vector`), the cached `end` iterator in the first version may become invalid, leading to undefined behavior.The second version obtains a fresh `end` iterator each time, making it safer when container type or modification are uncertain.

	In summary :
-First version : potentially faster but risks invalid iterator if the container changes.
- Second version : slightly less efficient but more robust and safer with unknown or mutable containers.

Choosing between them depends on container type knowledge and modification patterns during iteration.
*/

/*
Comment 3.

 Would it be reasonable to split void process_connections(connection_set & connections) in @Listing 4.10.h to have two
  different threads for connection.has_incoming_data() and connection.has_outgoing_data()? I think this would prevent
  sent_ok and received_payload from waiting for each other later in @4.2.3.cpp, int main().

✦ Yes, it would be reasonable to split the logic within void process_connections into two separate threads: one dedicated to
  handling connection.has_incoming_data() and another for connection.has_outgoing_data().

  This approach would indeed prevent sent_ok and received_payload from waiting on each other due to potential blocking
  within a single processing thread. By parallelizing these operations, you reduce the chance that heavy incoming data
  processing delays outgoing data fulfillment, or vice-versa, thus improving the overall responsiveness and concurrency of
  your connection handling.
*/
#pragma endregion //MINE
