#pragma once

#include "Listing C.1.h"

namespace messaging {
class sender {
	queue* q; // sender is a wrapper around the queue pointer.
public:
	sender() : q(nullptr) {} // Default-constructed sender has no queue
	explicit sender(queue* q_) : q(q_) {} // Allow construction from pointer to queue

	template<typename Message>
	void send(Message const& msg) {
		if (q) {
			q->push(msg); // Sending pushes message on the queue
		}
	}
};
}