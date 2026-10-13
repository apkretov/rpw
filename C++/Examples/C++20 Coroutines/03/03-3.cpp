#if 0

#include <coroutine>
#include <iostream>
#include <print>
#include <thread>
//OFF #include "vld.h"
#include "../../stdafx.h"

struct ReturnObject {
	struct promise_type {
		ReturnObject get_return_object() {
			std::cout << std::this_thread::get_id() << " 002 get_return_object()" << std::endl; //MINE
			return {};
		}

		std::suspend_never initial_suspend() {
			std::cout << std::this_thread::get_id() << " 003 initial_suspend()" << std::endl; //MINE
			return {};
		}

		//ORIG std::suspend_never final_suspend() noexcept { // Returns std::suspend_never. The coroutine automatically destroys itself after it finishes, so the memory is cleaned up. // See the note below about final_suspend().
		std::suspend_always final_suspend() noexcept { //MINE // Returns std::suspend_always. W/o a ReturnObject wrapper's destructor destroying this struct's wrapped object, h.destroy() must be called explicitly in main to prevent a memory leak.
			std::cout << std::this_thread::get_id() << " 015 final_suspend()" << std::endl; //MINE
			return {};
		}

		void return_void() { // `return_void()` is called by the compiler when the coroutine reaches the end of its body without encountering a `co_return` statement that specifies a value. It's basically how the coroutine says, "I've finished my task, and I don't have a result to pass back." Since the `counter` function doesn't return anything, the runtime calls `return_void()` just before `final_suspend()`
			std::cout << std::this_thread::get_id() << " 014 return_void()" << std::endl; //MINE
		}
		void unhandled_exception() {}
	};
};

struct Awaiter {
	std::coroutine_handle<>* handle_out;

	explicit Awaiter(std::coroutine_handle<>* handle) : handle_out(handle) { //MINE
		std::println("{} 005 Awaiter() handle_out={:x} frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0);
	}

	bool await_ready() {
		std::println("{} 007 await_ready() handle_out={:x} handle_out->frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); //MINE 
		return false;
	}

	void await_suspend(std::coroutine_handle<> h) {
		std::println("{} 008 await_suspend() &h={:x} h.frame={:x} handle_out={:x} handle_out->frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address()), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); //MINE
		*handle_out = h;
	}

	void await_resume() { std::cout << std::this_thread::get_id() << " 011 await_resume()" << std::endl; } //MINE
};

ReturnObject counter(std::coroutine_handle<>* handle) {
	std::println("{} 004 counter() entry handle={:x} frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0); //MINE
	Awaiter awaiter{handle};

	//ORIG for (unsigned i = 0; ; ++i) { //MINE: Comment this out to call final_suspend() to print 015.
	for (unsigned i = 0; i < 3; ++i) { //MINE This calls final_suspend() and prints 015.
		std::println("\n{} 006 counter: {} handle={:x} frame={:x}", std::this_thread::get_id(), i, reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0);
		co_await awaiter;
	}
	std::println("{} 013 counter() handle={:x} frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0); //MINE
}

#ifndef MINE_PSEUDOCODE
ReturnObject __compiler_counter(std::coroutine_handle<>* handle_arg) { // Caller sees: counter(&h);
	void* __frame = ::operator new(__builtin_coroutine_frame_size()); // 1. Allocate coroutine frame (stores promise and local state)
	auto& promise = *new (__frame) promise_type;

	ReturnObject __return = promise.get_return_object(); // 2. Obtain the return object immediately // Calls promise.get_return_object() --> "002 get_return_object()"

	auto __initial_awaiter = promise.initial_suspend(); // 3. Begin coroutine execution, start at initial suspend point // Calls promise.initial_suspend() --> "003 initial_suspend()"
	if (!__initial_awaiter.await_ready()) {
		auto __handle = std::coroutine_handle<promise_type>::from_promise(promise);
		__initial_awaiter.await_suspend(__handle); // initial_suspend returns suspend_never here, so this is skipped
		return __return;
	}

	std::println("{} 004 counter() entry...", std::this_thread::get_id()); // 4. Run the coroutine body // --> "004 counter() entry..."
	Awaiter& awaiter = *new (static_cast<void*>(/* frame offset */)) Awaiter{handle_arg}; // Allocate 'Awaiter awaiter' in the coroutine frame // --> "005 Awaiter()"
	unsigned& i = *new (static_cast<void*>(/* frame offset */)) unsigned(); // Local variable 'i' stored in the coroutine frame
	for (i = 0; i < 3; ++i) {
		std::println("\n{} 006 counter: {}...", std::this_thread::get_id(), i); // --> "006 counter: i..."

		auto& __awaiter = awaiter; // co_await awaiter; desugars into this
		if (!__awaiter.await_ready()) { // Calls awaiter.await_ready() --> "007 await_ready()"
			auto __handle = std::coroutine_handle<promise_type>::from_promise(promise);
			__awaiter.await_suspend(__handle); // Calls awaiter.await_suspend(__handle) --> "008 await_suspend()"
			return __return; // Ramp function returns return object here! Coroutine suspends.
		}
		__awaiter.await_resume(); // Runs when resumed --> "011 await_resume()"
	}

	std::println("{} 013 counter() exiting...", std::this_thread::get_id()); // --> "013 counter()"

	promise.return_void(); // 5. Reached the end of the coroutine body // Calls promise.return_void() --> "014 return_void()"

	auto __final_awaiter = promise.final_suspend(); // 6. Final suspend point // Calls promise.final_suspend() --> "015 final_suspend()"
	if (!__final_awaiter.await_ready()) {
		auto __handle = std::coroutine_handle<promise_type>::from_promise(promise);
		__final_awaiter.await_suspend(__handle); // Suspends frame; explicitly destroyed later via h.destroy() in main
	}
}
#endif // MINE_PSEUDOCODE

int main() {
	print_file_line();

	std::coroutine_handle<> h;
	std::println("{} 001 main before counter &h={:x} h.frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
	counter(&h);
	std::println("{} 009 main after counter &h={:x} h.frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE

	for (int i = 0; i < 3; ++i) {
		std::println("\n{} 010 main: before resume &h={:x} h.frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
		h();
		std::println("{} 012 main: after resume &h={:x} h.frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
	}

	h.destroy();
}
#endif // 0

/*
The note below about final_suspend()

---

**User**

Why does returning std::suspend_never clean up memory? @03-1.cpp:19-21

---

**Cursor**

`final_suspend()` is the last await point before the coroutine frame is eligible for destruction. What it returns decides whether the frame is destroyed for you or left alive.

## What happens at the end of a coroutine

When `counter` finishes (loop ends → `return_void()`), the runtime effectively does:

1. Call `promise.return_void()`
2. `co_await promise.final_suspend()`
3. **If that await does not suspend** → destroy the coroutine frame
4. **If it suspends** → leave the frame alive until something calls `handle.destroy()`

## Why `std::suspend_never` cleans up

`std::suspend_never::await_ready()` is `true`, so the await does not pause. Control falls through step 3, and the compiler-generated code destroys the frame (promise, locals, etc.).

That’s why VLD is happy with:

```19:22:c:\_\rpw\C++\Examples\C++20 Coroutines\03-1\03-1.cpp
		std::suspend_never final_suspend() noexcept { // Returns std::suspend_never. The coroutine automatically destroys itself after it finishes, so the memory is cleaned up.
		//MINE std::suspend_always final_suspend() noexcept { // Returns std::suspend_always - memory leaks.
			std::cout << std::this_thread::get_id() << " 015 final_suspend()" << std::endl; //MINE
			return {};
```

## Why `std::suspend_always` leaks here

`std::suspend_always` suspends at the final point. The frame stays allocated. In this sample, `h.destroy()` is commented out:

```67:67:c:\_\rpw\C++\Examples\C++20 Coroutines\03-1\03-1.cpp
	//ORIG h.destroy(); //MINE: Comment this out to call final_suspend() to print 015.
```

So nothing ever frees the frame → leak.

## Rule of thumb

| `final_suspend` returns | Frame lifetime |
|---|---|
| `suspend_never` | Destroyed automatically when the coroutine finishes |
| `suspend_always` | Kept until you call `destroy()` (or another owner does) |

`suspend_always` is common when a caller still needs the handle after completion (read a result, join, etc.). Fire-and-forget style (like this example) often uses `suspend_never` so cleanup is automatic — but then the handle must not be used after the final resume.
*/

/*
# Why are some handles of std::coroutine_handle\<promise_type> while the others of just std::coroutine_handle\<>? What is the default type of std::coroutine_handle\<>?


`std::coroutine_handle<>` is exactly `std::coroutine_handle<void>`: the template parameter has a default of `void`. It is a **type-erased** handle—useful for storing or passing any coroutine handle without knowing its promise type.[^1_1][^1_2]

## Two kinds of handle

| Type | Meaning | Typical use |
| :-- | :-- | :-- |
| `std::coroutine_handle<promise_type>` | Handle tied to a specific promise type; can access the promise via `.promise()` and can be created with `from_promise()` | Inside `promise_type::get_return_object()`, or when you need promise state |
| `std::coroutine_handle<>` | Handle with the promise type erased (`Promise = void`) | Generic APIs, awaiters, schedulers, storing “who suspended me” |

The standard defines:

```cpp
template<class Promise = void> struct coroutine_handle;
```

So these declarations are identical:

```cpp
std::coroutine_handle<> h;
std::coroutine_handle<void> h;
```

`coroutine_handle<void>` erases the promise type and is implicitly convertible from other specializations, such as `coroutine_handle<ReturnObject::promise_type>`.

## In your code

Your `ReturnObject` needs the concrete promise type because it constructs the handle from the promise:

```cpp
std::coroutine_handle<promise_type>::from_promise(*this)
```

Only `coroutine_handle<promise_type>` has `from_promise()` and `.promise()` for that particular promise type.

But `Awaiter::await_suspend()` receives the handle of whichever coroutine is currently executing the `co_await`. The awaiter does not need—and should not assume—that coroutine’s promise type, so the standard passes a type-erased handle:

```cpp
void await_suspend(std::coroutine_handle<> h) {
	*handle_out = h;
}
```

That is why `Awaiter` stores `std::coroutine_handle<>*`: it can later resume the suspended coroutine through `h.resume()` or `h()` without caring what its promise type is.

## Conversion direction

This works:

```cpp
std::coroutine_handle<ReturnObject::promise_type> specific = ...;
std::coroutine_handle<> generic = specific; // OK
```

This does **not** work directly:

```cpp
std::coroutine_handle<> generic = ...;
std::coroutine_handle<ReturnObject::promise_type> specific = generic; // error
```

Type erasure is one-way: once you convert to `coroutine_handle<>`, the compiler no longer knows which promise type it had. If you need the promise later, keep the typed handle or recover it through a design that preserves that information.

So, in short: **use the typed handle when you need the promise; use `std::coroutine_handle<>` when you only need to resume, destroy, or pass around a coroutine generically.**
*/
