#pragma once

#include "Listing C.1.h"
#include "Listing C.5.h"
#include "Listing C.6.h"
#include "messaging_config.h"
#include <functional>
#include <utility>

namespace messaging {
class close_queue {}; // The message for closing the queue

#if USE_TEMPLATES

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
		DISPATCH_TRACE("dispatcher", "move_ctor");
		other.chained = true; // The source shouldn't wait for messages.
	}

	explicit dispatcher(queue* q_) : q(q_), chained(false) {}

	template<typename Message, typename Func> // 3 Handle a specific type of message with a TemplateDispatcher.
	TemplateDispatcher<dispatcher, Message, Func> handle(Func&& f) {
		return TemplateDispatcher<dispatcher, Message, Func>(q, this, std::forward<Func>(f));
	}

	~dispatcher() noexcept(false) { // 4 The destructor might throw exceptions.
		DISPATCH_TRACE("dispatcher", "dtor");
		if (!chained) {
			wait_and_dispatch();
		}
	}
};

#else // !USE_TEMPLATES

class dispatcher : public dispatch_link {
	void wait_and_dispatch() {
		for (;;) {
			auto msg = q->wait_and_pop();
			dispatch(msg);
		}
	}

	bool dispatch(std::shared_ptr<message_base> const& msg) override {
		if (dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
			throw close_queue();
		}
		return false;
	}

#define MESSAGING_DEFINE_HANDLE(Msg) \
	chain_dispatcher handle_##Msg(std::function<void(Msg const&)> f) { \
		return chain_dispatcher(q, this, [fn = std::move(f)](std::shared_ptr<message_base> const& msg) -> bool { \
			if (wrapped_message<Msg>* w = dynamic_cast<wrapped_message<Msg>*>(msg.get())) { \
				fn(w->contents); \
				return true; \
			} \
			return false; \
		}); \
	}

public:
	dispatcher(dispatcher const&) = delete;
	dispatcher& operator=(dispatcher const&) = delete;

	dispatcher(dispatcher&& other) : dispatch_link(other.q, other.chained) {
		DISPATCH_TRACE("dispatcher", "move_ctor");
		other.chained = true;
	}

	explicit dispatcher(queue* q_) : dispatch_link(q_, false) {}

	MESSAGING_DEFINE_HANDLE(verify_pin)
	MESSAGING_DEFINE_HANDLE(withdraw)
	MESSAGING_DEFINE_HANDLE(get_balance)
	MESSAGING_DEFINE_HANDLE(withdrawal_processed)
	MESSAGING_DEFINE_HANDLE(cancel_withdrawal)
	MESSAGING_DEFINE_HANDLE(withdraw_ok)
	MESSAGING_DEFINE_HANDLE(withdraw_denied)
	MESSAGING_DEFINE_HANDLE(cancel_pressed)
	MESSAGING_DEFINE_HANDLE(balance)
	MESSAGING_DEFINE_HANDLE(withdraw_pressed)
	MESSAGING_DEFINE_HANDLE(balance_pressed)
	MESSAGING_DEFINE_HANDLE(pin_verified)
	MESSAGING_DEFINE_HANDLE(pin_incorrect)
	MESSAGING_DEFINE_HANDLE(digit_pressed)
	MESSAGING_DEFINE_HANDLE(clear_last_pressed)
	MESSAGING_DEFINE_HANDLE(card_inserted)
	MESSAGING_DEFINE_HANDLE(issue_money)
	MESSAGING_DEFINE_HANDLE(display_insufficient_funds)
	MESSAGING_DEFINE_HANDLE(display_enter_pin)
	MESSAGING_DEFINE_HANDLE(display_enter_card)
	MESSAGING_DEFINE_HANDLE(display_balance)
	MESSAGING_DEFINE_HANDLE(display_withdrawal_options)
	MESSAGING_DEFINE_HANDLE(display_withdrawal_cancelled)
	MESSAGING_DEFINE_HANDLE(display_pin_incorrect_message)
	MESSAGING_DEFINE_HANDLE(eject_card)

#undef MESSAGING_DEFINE_HANDLE

	~dispatcher() noexcept(false) {
		DISPATCH_TRACE("dispatcher", "dtor");
		if (!chained) {
			wait_and_dispatch();
		}
	}
};

#endif // USE_TEMPLATES
}
