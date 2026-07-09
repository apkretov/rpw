#pragma once

#include "Listing C.1.h"
#include <algorithm>
#include <memory>
#include <utility>

namespace messaging {
template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
	queue* q;
	PreviousDispatcher* prev;
	Func f;
	bool chained;
	TemplateDispatcher(TemplateDispatcher const&) = delete;
	TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

	template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
	friend class TemplateDispatcher; // TemplateDispatcher instantiations are friends of each other.

	void wait_and_dispatch() {
		for (;;) {
			auto msg = q->wait_and_pop();
			if (dispatch(msg)) // 1 If you handle the message, break out of the loop.
				break;
		}
	}

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (wrapped_message<Msg>* wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) { // 2 Check the message type and call the function.
			f(wrapper->contents);
			return true;
		} else {
			return prev->dispatch(msg); // 3 Chain to the previous dispatcher.
		}
	}
public:
	TemplateDispatcher(TemplateDispatcher&& other) : q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained) {
		other.chained = true;
	}

	TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) : q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false) {
		prev_->chained = true;
	}

	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) { // 4 Additional handlers can be chained.
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}

	~TemplateDispatcher() noexcept(false) { // 5 The destructor is noexcept(false) again.
		if (!chained) {
			wait_and_dispatch();
		}
	}
};
}