#pragma once

#include "message_queue.h"
#include <utility>
#include <memory>

struct close_queue {};

// Forward declaration so the handle template and friend declaration can reference it
template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher;

class dispatcher {
	message_queue* q;
	bool chained = false;

	// Grant all instances of TemplateDispatcher access to our private 'chained' member
	template<typename D, typename M, typename F>
	friend class TemplateDispatcher;

public:
	dispatcher(dispatcher const&) = delete;
	dispatcher& operator=(dispatcher const&) = delete;

	dispatcher(dispatcher&& other) : q(other.q), chained(other.chained) {
		other.chained = true;
	}

	explicit dispatcher(message_queue* q_) : q(q_), chained(false) {}

	template<typename Msg, typename Func>
	TemplateDispatcher<dispatcher, Msg, Func> handle(Func&& f) {
		chained = true;
		return TemplateDispatcher<dispatcher, Msg, Func>(q, this, std::forward<Func>(f));
	}

	bool dispatch(std::shared_ptr<message_base> const& msg) {
		if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
			throw close_queue();
		}
		return false;
	}

	~dispatcher() noexcept(false) {
		if (!chained) {
			for (;;) {
				if (dispatch(q->wait_and_pop())) break;
			}
		}
	}
};

// Defer inclusion to the bottom to resolve circular dependency
#include "template_dispatcher.h"