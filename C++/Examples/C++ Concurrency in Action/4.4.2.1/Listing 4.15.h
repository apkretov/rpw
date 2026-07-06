#pragma once

#include "receiver.h"
#include "sender.h"
#include "close_queue.h"
#include "simulator_components.h"
#include <print>
#include <string>

struct card_inserted {
    std::string account;
};

class atm {
    messaging::receiver* incoming;
    messaging::sender* bank;
    messaging::sender* interface_hardware;
    void (atm::*state)();
    std::string account;
    std::string pin;
    
    void waiting_for_card() { // 1 Waiting for card state function
        interface_hardware->send(display_enter_card()); // 2 Display entry message

        incoming->wait() // 3 Wait for a message //MINE See the note below.
            .handle<card_inserted>([&](card_inserted const& msg) { // 4 Handle with a lambda
                account = msg.account;
                pin = "";
                interface_hardware->send(display_enter_pin());
                state = &atm::getting_pin;
            });
    }
    
    void getting_pin();
    
    void verifying_pin() { 
		std::println("[ATM] Verifying PIN... Transiting back to idle."); //ORIG std::cout << "[ATM] Verifying PIN... Transiting back to idle.\n";
        state = &atm::waiting_for_card; 
    }

	void done_processing() { 
		std::println("[ATM] Session Cancelled/Done."); //ORIG std::cout << "[ATM] Session Cancelled/Done.\n";
        state = &atm::waiting_for_card; 
    }
public:
    atm(messaging::receiver* inc, messaging::sender* bnk, messaging::sender* hw) : incoming(inc), bank(bnk), interface_hardware(hw) {}

    void run() { // 5 Execution starts here
		state = &atm::waiting_for_card; // 6 Set initial state
        try {
            for(;;) {
                (this->*state)(); // 7 Repeatedly execute current state
            }
        }
        catch(messaging::close_queue const&) {}
    }
};

/*
The note

# What happens, if the returned dispatcher receives an event other than card_inserted? Will it simply skip that event? If so, wouldn’t that event be lost because it was sent to the wrong destination? The correct destination would never receive the event if this call discards it. I may have misunderstood something — please explain how this works.

No — in this design, an unmatched event is not “lost to the wrong destination” in the way you’re imagining. The important detail is that `incoming->wait()` returns the **next message from the ATM’s own queue**, and `handle<card_inserted>(...)` only decides whether the ATM reacts to that message; it does not route it somewhere else.

## How it works

Think of it like this:

1. A sender pushes a message into the ATM’s incoming queue.
2. `incoming->wait()` removes one message from that queue and hands it to the dispatcher.
3. The dispatcher checks the message type.
4. If it is `card_inserted`, the lambda runs.
5. If it is not `card_inserted`, that particular handler does nothing.

So yes, the specific call is effectively “skip if not matched,” but that does **not** mean the message should have gone somewhere else. The message was already delivered to the ATM queue, and the ATM consumed it.

## Why this is not a bug

This code assumes that the ATM has only one incoming stream of events, and the ATM itself is responsible for deciding what each event means in the current state. That is normal for an event loop or state-machine design.

For example:

- In `waiting_for_card()`, only `card_inserted` matters.
- In `getting_pin()`, only `digit_pressed`, `clear_last_pressed`, and `cancel_pressed` matter.

An event that arrives while the ATM is in the wrong state is simply ignored by that state handler. That is not “misrouting”; it is state-based filtering.

## The subtle point

Your concern would be valid if there were a central router that removed a message from a shared bus and then failed to forward it to the right consumer. But this code is not built that way. Each `wait()` call removes the message from one queue, and the current state function decides what to do with it.

So if a `digit_pressed` arrives while the ATM is waiting for a card, the current implementation will not process it. In that sense, yes, it is discarded by that state. That is usually acceptable because the user interface should only generate events that make sense for the current flow, or the system should add buffering/requeueing logic if needed.

## If you wanted to keep unmatched events

Then you would need a different design, for example:

- requeue the message,
- store it for later,
- or use a central dispatcher that delivers events to multiple listeners.

But this code does not do that. It is a single-consumer, state-driven message loop, so “unhandled” means “ignored by the current state,” not “forwarded elsewhere.”

## One-sentence summary

So the key idea is: **the event is not sent to the wrong destination; it is received by the ATM, and the current state decides whether that event matters.**
*/