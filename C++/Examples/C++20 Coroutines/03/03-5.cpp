	#if 1

#include <coroutine>
#include <iostream>
#include <print>
#include <thread>
#include "vld.h"
#include "../../stdafx.h"

struct ReturnObject {
	struct promise_type;
	std::coroutine_handle<promise_type> handle{}; //MINE

	explicit ReturnObject(std::coroutine_handle<promise_type> h) : handle(h) {} //MINE

	struct promise_type {
		ReturnObject get_return_object() {
			std::cout << std::this_thread::get_id() << " 002 get_return_object()" << std::endl; //MINE
			//ORIG return {};
			return ReturnObject{std::coroutine_handle<promise_type>::from_promise(*this)}; //MINE
		}

		//ORIG std::suspend_never initial_suspend() {
		std::suspend_always initial_suspend() { //MINE //  By pausing at the beginning with `initial_suspend` returning `suspend_always`, you're telling the coroutine to hold on. You then grab the necessary handle from the return object and use that to resume execution right when you want to, typically after filling a pointer or something like that that the coroutine needs. It ensures everything is in place before the main body starts running. 
			std::cout << std::this_thread::get_id() << " 003 initial_suspend()" << std::endl; //MINE
			return {};
		}

		//ORIG std::suspend_never final_suspend() noexcept { // Returns std::suspend_never. The coroutine automatically destroys itself after it finishes, so the memory is cleaned up. // See the note below about final_suspend().
		std::suspend_always final_suspend() noexcept { //MINE // Returns std::suspend_always. W/o a ReturnObject wrapper's destructor destroying this struct's wrapped object, h.destroy() must be called explicitly in main to prevent a memory leak.
			std::cout << std::this_thread::get_id() << " 017 final_suspend()" << std::endl; //MINE
			return {};
		}

		void return_void() { // `return_void()` is called by the compiler when the coroutine reaches the end of its body without encountering a `co_return` statement that specifies a value. It's basically how the coroutine says, "I've finished my task, and I don't have a result to pass back." Since the `counter` function doesn't return anything, the runtime calls `return_void()` just before `final_suspend()`
			std::cout << std::this_thread::get_id() << " 016 return_void()" << std::endl; //MINE
		}
		void unhandled_exception() {}
	};
};

struct Awaiter {
	std::coroutine_handle<>* handle_out;

	explicit Awaiter(std::coroutine_handle<>* handle) : handle_out(handle) { //MINE
		std::print("{} 006 Awaiter() handle_out={:x} frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0);
	}

	bool await_ready() {
		std::print("{} 008 await_ready() handle_out={:x} handle_out->frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); //MINE 
		return false;
	}

	void await_suspend(std::coroutine_handle<> h) {
		std::print("{} 009 await_suspend() &h={:x} h.frame={:x} handle_out={:x} handle_out->frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address()), reinterpret_cast<std::uintptr_t>(handle_out), handle_out ? reinterpret_cast<std::uintptr_t>(handle_out->address()) : 0); //MINE
		*handle_out = h;
	}

	//ORIG void await_resume() { 
	int await_resume() { //MINE The return value becomes the value of the co_await expression. So it's not always void. E.g. below: int x = co_await awaiter;  It's used whenever your coroutine needs to produce a result that you want to use immediately after the `co_await` expression. Think about fetching data from a website, reading a file, or perhaps waiting for a computation to finish. Instead of just waiting, the `co_await` can directly return that data, or the result, so you can keep working with it right away. 
		constexpr int return_value = 42; //MINE
		std::cout << std::this_thread::get_id() << " 012 await_resume(): returns " << return_value << std::endl; //MINE
		return return_value; //MINE
	}
};

ReturnObject counter(std::coroutine_handle<>* handle) {
	std::print("{} 005 counter() entry handle={:x} frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0); //MINE
	Awaiter awaiter{handle};

	//ORIG for (unsigned i = 0; ; ++i) { //MINE: Comment this out to call final_suspend() to print 017.
	for (unsigned i = 0; i < 3; ++i) { //MINE This calls final_suspend() and prints 017.
		std::print("\n{} 007 counter: {} handle={:x} frame={:x}\n", std::this_thread::get_id(), i, reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0);
		//ORIG co_await awaiter; 
		int x = co_await awaiter; //MINE
		std::print("{} 013 counter: co_await returned {}\n", std::this_thread::get_id(), x); //MINE
	}
	std::println("{} 015 counter() handle={:x} frame={:x}", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(handle), handle ? reinterpret_cast<std::uintptr_t>(handle->address()) : 0); //MINE
}

#ifdef MINE_PSEUDOCODE
ReturnObject __compiler_counter(std::coroutine_handle<>* handle_arg) { // Caller (main) sees: counter(&h); // Compiler-generated “ramp” function for the coroutine
	void* __frame = ::operator new(__builtin_coroutine_frame_size()); // 1. Allocate coroutine frame (promise, locals, etc.)
	auto& promise = *new (__frame) promise_type;

	ReturnObject __return = promise.get_return_object(); // 2. Obtain the return object immediately // Calls promise.get_return_object() --> "002 get_return_object()"

	auto __initial_awaiter = promise.initial_suspend(); // 3. Begin coroutine execution, start at initial suspend point // Calls promise.initial_suspend() --> "003 initial_suspend()"
	if (!__initial_awaiter.await_ready()) {
		auto __handle = std::coroutine_handle<promise_type>::from_promise(promise); // Gets handle to self
		__initial_awaiter.await_suspend(__handle); // (suspends here if await_ready returns false, but yours returns true)
		return __return; // Ramp function returns return object here if it suspends
	}

	/*
	4. Run the coroutine body
		"005 counter() entry...", allocates 'Awaiter awaiter{handle_arg}'
		--> "006 Awaiter()"
		Loop with 'std::print("\n... counter: ...")'
		--> "007 counter: 0 ..."
	*/

	{ // co_await awaiter;
		auto& __awaiter = awaiter;
		if (!__awaiter.await_ready()) { // Calls awaiter.await_ready() --> "008 await_ready()"
			auto __handle = std::coroutine_handle<promise_type>::from_promise(promise); // Gets handle to self
			__awaiter.await_suspend(__handle); // Calls awaiter.await_suspend(__handle) --> "009 await_suspend()"
			return __return; // Ramp function returns return object now! Coroutine is suspended.
		}
		__awaiter.await_resume();  // runs when resumed --> " 012 await_resume()"
	}

	/*
	(Coroutine continues loop and suspend cycle)
	After loops finish: // --> "015 counter()"
	*/

	promise.return_void(); // --> "016 return_void()"

	auto __final_awaiter = promise.final_suspend(); // Final suspend point // --> "017 final_suspend()"
	if (!__final_awaiter.await_ready()) {
		auto __handle = std::coroutine_handle<promise_type>::from_promise(promise); // Gets handle to self
		__final_awaiter.await_suspende(__handle); // Without wrapper, this suspends frame.
	}

	// Frame destroyed here if not suspended, or later via handle.destroy()
}
#endif // MINE_PSEUDOCODE

int main() {
	print_file_line();

	std::coroutine_handle<> h;
	std::print("{} 001 main before counter &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE

	//ORIG counter(&h);
	auto ro = counter(&h); //MINE
	h = ro.handle; //MINE Valid already: initial_suspend suspended before Awaiter could fill h.
	std::print("{} 004 main: initially suspended &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
	h.resume(); //MINE Leave initial_suspend; run body to first co_await.

	std::print("{} 010 main after first resume &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE

	for (int i = 0; i < 3; ++i) {
		std::print("\n{} 011 main: before resume &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
		h();
		std::print("{} 014 main: after resume &h={:x} h.frame={:x}\n", std::this_thread::get_id(), reinterpret_cast<std::uintptr_t>(&h), reinterpret_cast<std::uintptr_t>(h.address())); //MINE
	}

	h.destroy(); //MINE required because final_suspend is suspend_always
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
			std::cout << std::this_thread::get_id() << " 017 final_suspend()" << std::endl; //MINE
			return {};
```

## Why `std::suspend_always` leaks here

`std::suspend_always` suspends at the final point. The frame stays allocated. In this sample, `h.destroy()` is commented out:

```67:67:c:\_\rpw\C++\Examples\C++20 Coroutines\03-1\03-1.cpp
	//ORIG h.destroy(); //MINE: Comment this out to call final_suspend() to print 017.
```

So nothing ever frees the frame → leak.

## Rule of thumb

| `final_suspend` returns | Frame lifetime |
|---|---|
| `suspend_never` | Destroyed automatically when the coroutine finishes |
| `suspend_always` | Kept until you call `destroy()` (or another owner does) |

`suspend_always` is common when a caller still needs the handle after completion (read a result, join, etc.). Fire-and-forget style (like this example) often uses `suspend_never` so cleanup is automatic — but then the handle must not be used after the final resume.
*/
#endif // 0
