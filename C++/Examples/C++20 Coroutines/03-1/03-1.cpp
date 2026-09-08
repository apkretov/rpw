#include <coroutine>
#include <cstdint>
#include <iostream>
#include <print>
#include <thread>
#include "vld.h"
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
			std::cout << std::this_thread::get_id() << " 014 final_suspend()" << std::endl; //MINE
			return {}; 
		}

		void return_void() { std::cout << std::this_thread::get_id() << " 013 return_void()" << std::endl; } //MINE
		void unhandled_exception() {}
	};
};

struct Awaiter {
	std::coroutine_handle<>* handle_out;

	explicit Awaiter(std::coroutine_handle<>* handle) : handle_out(handle) { //MINE
		std::print("{} 005 Awaiter() handle_out={:x} frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); 
	}

	bool await_ready() { 
		std::print("{} 007 await_ready() handle_out={:x} handle_out->frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle_out) , handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); //MINE 
		return false;
	}

	void await_suspend(std::coroutine_handle<> h) { 
		std::print("{} 008 await_suspend() &h={:x} h.frame={:x} handle_out={:x} handle_out->frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address()), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); //MINE
		*handle_out = h;
	}

	void await_resume() { std::cout << std::this_thread::get_id() << " 011 await_resume()" << std::endl; } //MINE
};

ReturnObject counter(std::coroutine_handle<>* handle) {
	std::print("{} 004 counter() entry handle={:x} frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0); //MINE
	Awaiter awaiter{handle};

	//ORIG for (unsigned i = 0; ; ++i) { //MINE: Comment this out to call final_suspend() to print 014.
	for (unsigned i = 0; i < 3; ++i) { //MINE This calls final_suspend() and prints 014.
		std::print("\n{} 006 counter: {} handle={:x} frame={:x}\n", std::this_thread::get_id(), i, reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0);
		co_await awaiter;
	}
}

int main() {
	print_file_line();

	std::coroutine_handle<> h;
	std::print("{} 001 main before counter &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
	counter(&h);
	std::print("{} 009 main after counter &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE

	for (int i = 0; i < 3; ++i) {
		std::print("\n{} 010 main: before resume &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
		h();
		std::print("{} 012 main: after resume &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
	}

	h.destroy();
}

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
			std::cout << std::this_thread::get_id() << " 014 final_suspend()" << std::endl; //MINE
			return {};
```

## Why `std::suspend_always` leaks here

`std::suspend_always` suspends at the final point. The frame stays allocated. In this sample, `h.destroy()` is commented out:

```67:67:c:\_\rpw\C++\Examples\C++20 Coroutines\03-1\03-1.cpp
	//ORIG h.destroy(); //MINE: Comment this out to call final_suspend() to print 014.
```

So nothing ever frees the frame → leak.

## Rule of thumb

| `final_suspend` returns | Frame lifetime |
|---|---|
| `suspend_never` | Destroyed automatically when the coroutine finishes |
| `suspend_always` | Kept until you call `destroy()` (or another owner does) |

`suspend_always` is common when a caller still needs the handle after completion (read a result, join, etc.). Fire-and-forget style (like this example) often uses `suspend_never` so cleanup is automatic — but then the handle must not be used after the final resume.
*/
