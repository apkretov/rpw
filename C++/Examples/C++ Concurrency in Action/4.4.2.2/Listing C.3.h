#pragma once

#include "Listing C.1.h"
#include "Listing C.2.h"
#include "Listing C.4.h"

namespace messaging {
class receiver {
	queue q; // A receiver owns the queue.
public:
	operator sender() { return sender(&q); } // Allow implicit conversion to a sender that references the queue.
	dispatcher wait() { return dispatcher(&q); } // Waiting for a queue creates a dispatcher
};
}