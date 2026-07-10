#pragma once

#include "message_queue.h"
#include <utility>
#include <memory>

template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
public:
	TemplateDispatcher(message_queue* q_, PreviousDispatcher* prev_, Func&& f_) : q(q_), prev(prev_), f(std::forward<Func>(f_)) {
		prev_->chained = true; // Mark previous handler link as chained
	}

	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) { // Additional handlers chained
		chained = true;
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}

	TemplateDispatcher(TemplateDispatcher const&) = delete;
	TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

	TemplateDispatcher(TemplateDispatcher&& other) noexcept : q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained) {
		other.chained = true;
	}

	~TemplateDispatcher() noexcept(false) { if (!chained) wait_and_dispatch(); } // Destructor is noexcept(false) to propagate throw
private:
	message_queue* q;
	PreviousDispatcher* prev; // Pointer back to the previous dispatcher link 
	Func f;
	bool chained = false;

	template<typename D, typename M, typename F>
	friend class TemplateDispatcher; // TemplateDispatcher instantiations are friends of each other

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) { // Check type and process
			f(wrapper->contents); // Call user payload function
			return true;
		}
		return prev->dispatch(msg); // Chain to the previous dispatcher
	}

	void wait_and_dispatch() {
		for (;;) {
			auto msg = q->wait_and_pop();
			if (dispatch(msg)) break; // Break out of processing loop if handled
		}
	}
};
