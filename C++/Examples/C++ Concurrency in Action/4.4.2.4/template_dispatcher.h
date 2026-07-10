#pragma once

#include "message_queue.h"
#include <utility>
#include <memory>

template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher {
	message_queue* q;
	PreviousDispatcher* prev; // Pointer back to the previous dispatcher link 
	Func f;
	bool chained = false;

	template<typename D, typename M, typename F>
	friend class TemplateDispatcher; // TemplateDispatcher instantiations are friends of each other [cite: 28]

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (auto wrapper = dynamic_cast<wrapped_message<Msg>*>(msg.get())) { // Check type and process [cite: 30]
			f(wrapper->contents); // Call user payload function [cite: 31]
			return true;
		}
		return prev->dispatch(msg); // Chain to the previous dispatcher [cite: 32]
	}

	void wait_and_dispatch() {
		for (;;) {
			auto msg = q->wait_and_pop();
			if (dispatch(msg)) break; // Break out of processing loop if handled [cite: 29]
		}
	}

public:
	TemplateDispatcher(TemplateDispatcher const&) = delete;
	TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

	TemplateDispatcher(TemplateDispatcher&& other)
		: q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained) {
		other.chained = true;
	}

	TemplateDispatcher(message_queue* q_, PreviousDispatcher* prev_, Func&& f_)
		: q(q_), prev(prev_), f(std::forward<Func>(f_)) {
		prev_->chained = true; // Mark previous handler link as chained [cite: 34]
	}

	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) { // Additional handlers chained [cite: 34]
		chained = true;
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}

	~TemplateDispatcher() noexcept(false) { // Destructor is noexcept(false) to propagate throw [cite: 35]
		if (!chained) wait_and_dispatch();
	}
};
