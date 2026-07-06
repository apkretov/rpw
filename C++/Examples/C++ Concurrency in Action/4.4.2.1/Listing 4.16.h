#pragma once

#include "Listing 4.15.h"
#include "simulator_components.h"
#include <print>
#include <string>

inline void atm::getting_pin() {
    incoming->wait()
        .handle<digit_pressed>([&](digit_pressed const& msg) { // 1 Handle digit keypresses //MINE See the note below.
            unsigned const pin_length = 4;
            pin += msg.digit;
			std::println("[ATM] Digit entered: {}", msg.digit); //ORIG std::cout << "[ATM] Digit entered: " << msg.digit << "\n";
            if (pin.length() == pin_length) {
				bank->send(verify_pin(account, pin, *incoming));
                state=&atm::verifying_pin;
            }
        })
        .handle<clear_last_pressed>([&](clear_last_pressed const& msg) { // 2 Handle backspace/clear
            if (!pin.empty()) {
                pin.resize(pin.length() - 1);
				std::println("[ATM] Cleared last digit. Current length: {}", pin.length()); // ORIG	std::cout << "[ATM] Cleared last digit. Current length: " << pin.length() << "\n";
            }
		})
        .handle<cancel_pressed>([&](cancel_pressed const& msg) { // 3 Handle cancel transaction
			state = &atm::done_processing; 
		}); 
}

/*
The note

# I’m fine with that style, but I need to understand it because it’s new to me. Please give a simple, different example that is much simpler, and explain the basics of that syntax. Also include a reference to the standard C++ documentation.

Sure — the core idea is that this syntax is just a **template-based handler**: the type inside `<...>` tells the code what kind of message to look for. In your ATM code, `.handle<digit_pressed>(...)` means “if the received message is a `digit_pressed`, call this lambda.”


## Much simpler example

Here is a tiny example with just two message types:

```cpp
struct ping {};
struct stop {};

template <typename T>
struct box {
	T value;
};
```

That `template <typename T>` part means `T` is a placeholder type. C++ will substitute a real type later, like `int`, `ping`, or `stop`.

Now a very simple handler style:

```cpp
struct dispatcher {
	template <typename Message, typename Func>
	void handle(Message const& msg, Func f) {
		f(msg);
	}
};
```

Usage:

```cpp
dispatcher d;

ping p;
d.handle<ping>(p, [](ping const&) {
	std::cout << "got ping\n";
});
```

Here, `handle<ping>` tells the compiler that `Message` is `ping`. That is the basic syntax idea: the type in angle brackets is a template argument.

## What the syntax means

When you write:

```cpp
.handle<digit_pressed>(...)
```

you are calling a **templated member function**. The part in `<digit_pressed>` is not a runtime value; it is a compile-time type choice. The compiler generates a version of `handle` specialized for `digit_pressed`.

That is why this works:

```cpp
.handle<digit_pressed>([](digit_pressed const& msg) { ... })
```

The lambda’s parameter type matches the template argument. It is a common pattern in generic C++ code and event dispatching.

## Even simpler mental model

Think of it like this:

- `handle<MessageType>` = “make a version of this function for this message type.”
- `digit_pressed` = the selected type.
- The lambda = the code to run when that type arrives.

So your original chain is just several typed handlers in a row, each checking a different event type.

## Standard documentation

For the standard reference, the best starting point is the C++ template documentation on cppreference, which summarizes template syntax and usage clearly.

A useful reference link is: [Templates - cppreference](https://en.cppreference.com/cpp/language/templates)

## Applying it to your ATM code

In your ATM example, this:

```cpp
incoming->wait()
	.handle<digit_pressed>(...)
	.handle<clear_last_pressed>(...)
	.handle<cancel_pressed>(...);
```

means:

1. Wait for one message.
2. Try to interpret it as `digit_pressed`.
3. If that fails, try `clear_last_pressed`.
4. If that fails, try `cancel_pressed`.

So the angle-bracket syntax is simply “which message type are we handling?”
*/