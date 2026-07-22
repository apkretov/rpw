#pragma once

#include "message_queue.h"
#include <utility>
#include <memory>
#include "debug.h"

struct close_queue {};

template<typename PreviousDispatcher, typename Msg, typename Func>
class TemplateDispatcher; // Forward declaration so handle and friend can name it

class dispatcher {
	template<typename D, typename M, typename F>
	friend class TemplateDispatcher;
public:
	explicit dispatcher(message_queue* q_) : q(q_) { 
		#ifdef DEBUG
		std::println("dispatcher ctor");
		#endif
	}

	~dispatcher() noexcept(false) {
		if (!chained) 
			for (;;) // The last temporary in the chain (where chained is still false) runs the dispatch loop 
				if (dispatch(q->wait_and_pop())) 
					break; // Stop waiting once a message is successfully handled

		#ifdef DEBUG
		std::println("dispatcher dtor");
		#endif
	}

	template<typename Msg, typename Func>
	TemplateDispatcher<dispatcher, Msg, Func> handle(Func&& f) {
		#ifdef DEBUG
		std::println("dispatcher handle");
		#endif

		chained = true;
		return TemplateDispatcher<dispatcher, Msg, Func>(q, this, std::forward<Func>(f));
	}

private:
	message_queue* q;
	bool chained = false;

	bool dispatch(std::shared_ptr<message_base> const& msg) const {
		if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
			#ifdef DEBUG
			std::println("dispatcher throw close_queue");
			#endif

			throw close_queue();
		}
		return false;
	}
};

#include "template_dispatcher.h" // After dispatcher is complete (circular dependency)
