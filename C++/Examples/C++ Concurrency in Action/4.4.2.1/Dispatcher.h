#pragma once

#pragma region MINE
#include "message_base.h"
#include "wrapped_message.h"
#include "queue.h"
#include <memory>

namespace messaging {
struct dispatcher {
    explicit dispatcher(std::shared_ptr<message_base> msg_) : msg(msg_) {}

    std::shared_ptr<message_base> msg;
    bool handled = false;
		            
    template<typename Message, typename Func>
    dispatcher& handle(Func&& f) { //MINE See the note below.
        if (!handled && msg) {
            if (auto wrapper = dynamic_cast<wrapped_message<Message>*>(msg.get())) {
                f(wrapper->contents);
                handled = true;
            }
        }
        return *this;
    }
};
}
#pragma endregion //MINE

/*
The note

Why is f an rvalue reference?

Because Func&& in a function template is usually not a plain rvalue reference. When Func is deduced from the call, Func&& becomes a forwarding reference: it can bind to both lvalues and rvalues.

In a non-template example, T&& means “rvalue reference.” But in a template like:
template <typename Message, typename Func>
dispatcher& handle(Func&& f)

Func is deduced from the argument you pass. If you pass an lvalue lambda, Func may deduce to a reference type, and reference-collapsing rules make Func&& become an lvalue reference. If you pass a temporary lambda, it can stay an rvalue reference.

Simple rule
•	T&& in a normal function parameter: rvalue reference.
•	T&& in a deduced template parameter: forwarding reference.[81][83]
So handle(Func&& f) is written that way because it wants to accept any callable efficiently, whether the caller passes a temporary lambda or an existing function object.

Why not const Func&?
You could write:
template <typename Message, typename Func>
dispatcher& handle(Func const& f)

That works for many cases, but it is less flexible. A forwarding reference lets the function accept more kinds of callables and preserve value category when needed.[82][81]
In your code specifically
Your lambda:
[&](digit_pressed const& msg) { ... }

is a temporary callable object at the call site, so Func&& is a natural choice. The function is not trying to modify the callable; it is just forwarding it into the dispatch logic.[84][82]
Tiny intuition
Think of Func&& here as “give me whatever callable you have, and I’ll adapt to it.” That is the same technique used in perfect forwarding.
*/