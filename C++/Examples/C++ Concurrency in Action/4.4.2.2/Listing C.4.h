#pragma once

#include "Listing C.1.h"
#include "Listing C.5.h"
#include <utility>

namespace messaging {
class close_queue {}; // The message for closing the queue

class dispatcher {
	queue* q;
	bool chained;
	dispatcher(dispatcher const&) = delete; // dispatcher instances cannot be copied.
	dispatcher& operator=(dispatcher const&) = delete;

	template<typename Dispatcher, typename Msg, typename Func>
	friend class TemplateDispatcher; // Allow TemplateDispatcher instances to access the internals.

	void wait_and_dispatch() {
		for (;;) { // 1 Loop, waiting for, and dispatching messages
			auto msg = q->wait_and_pop();
			dispatch(msg);
		}
	}

	bool dispatch(std::shared_ptr<message_base> const& msg) { // 2 dispatch() checks for a close_queue message, and throws.
		if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
			throw close_queue();
		}
		return false;
	}
public:
	dispatcher(dispatcher&& other) : q(other.q), chained(other.chained) { // Dispatcher instances can be moved.
		other.chained = true; // The source shouldn't wait for messages.
	}

	explicit dispatcher(queue* q_) : q(q_), chained(false) {}

	template<typename Message, typename Func> // 3 Handle a specific type of message with a TemplateDispatcher.
	TemplateDispatcher<dispatcher, Message, Func> handle(Func&& f) {
		return TemplateDispatcher<dispatcher, Message, Func>(q, this, std::forward<Func>(f));
	}

	~dispatcher() noexcept(false) { // 4 The destructor might throw exceptions.
		if (!chained) {
			wait_and_dispatch();
		}
	}
};
}
