#pragma once

#include "Listing C.1.h"
#include "messaging_config.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>

namespace messaging {
#if USE_TEMPLATES

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
		DISPATCH_TRACE("TemplateDispatcher", "move_ctor");
		other.chained = true;
	}

	TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) : q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false) {
		DISPATCH_TRACE("TemplateDispatcher", "link_ctor");
		prev_->chained = true;
	}

	template<typename OtherMsg, typename OtherFunc>
	TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc> handle(OtherFunc&& of) { // 4 Additional handlers can be chained.
		return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
	}

	~TemplateDispatcher() noexcept(false) { // 5 The destructor is noexcept(false) again.
		DISPATCH_TRACE("TemplateDispatcher", "dtor");
		if (!chained) {
			wait_and_dispatch();
		}
	}
};

#else // !USE_TEMPLATES

#include "Listing C.6.h"

class dispatcher;

class dispatch_link {
protected:
	queue* q;
	bool chained;
	friend class chain_dispatcher;
	friend class dispatcher;
	virtual bool dispatch(std::shared_ptr<message_base> const& msg) = 0;
	dispatch_link(queue* q_, bool chained_) : q(q_), chained(chained_) {}
public:
	dispatch_link(dispatch_link const&) = delete;
	dispatch_link& operator=(dispatch_link const&) = delete;
	virtual ~dispatch_link() noexcept(false) = default;
};

class chain_dispatcher : public dispatch_link {
	friend class dispatcher;
	dispatch_link* prev;
	std::function<bool(std::shared_ptr<message_base> const&)> try_handle;

	void wait_and_dispatch() {
		for (;;) {
			auto msg = q->wait_and_pop();
			if (dispatch(msg))
				break;
		}
	}

	bool dispatch(std::shared_ptr<message_base> const& msg) override {
		if (try_handle(msg))
			return true;
		return prev->dispatch(msg);
	}

	chain_dispatcher(queue* q_, dispatch_link* prev_, std::function<bool(std::shared_ptr<message_base> const&)> try_handle_)
		: dispatch_link(q_, false), prev(prev_), try_handle(std::move(try_handle_)) {
		DISPATCH_TRACE("chain_dispatcher", "link_ctor");
		prev_->chained = true;
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
	chain_dispatcher(chain_dispatcher const&) = delete;
	chain_dispatcher& operator=(chain_dispatcher const&) = delete;

	chain_dispatcher(chain_dispatcher&& other)
		: dispatch_link(other.q, other.chained), prev(other.prev), try_handle(std::move(other.try_handle)) {
		DISPATCH_TRACE("chain_dispatcher", "move_ctor");
		other.chained = true;
	}

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

	~chain_dispatcher() noexcept(false) {
		DISPATCH_TRACE("chain_dispatcher", "dtor");
		if (!chained) {
			wait_and_dispatch();
		}
	}
};

#endif // USE_TEMPLATES
}
