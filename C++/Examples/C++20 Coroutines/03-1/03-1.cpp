#include <coroutine>
#include <iostream>
#include <thread>
#include "vld.h"
#include "../../stdafx.h"

struct ReturnObject {
	struct promise_type {
		ReturnObject get_return_object() { 
			std::cout << std::this_thread::get_id() << " 111 get_return_object()" << std::endl; //MINE
			return {}; 
		}

		std::suspend_never initial_suspend() { 
			std::cout << std::this_thread::get_id() << " 222 initial_suspend()" << std::endl; //MINE
			return {}; 
		}

		//ORIG std::suspend_never final_suspend() noexcept { // Returns std::suspend_never. The coroutine automatically destroys itself after it finishes, so the memory is cleaned up. // See the note below about final_suspend().
		std::suspend_always final_suspend() noexcept { //MINE // Returns std::suspend_always. h.destroy() must be called in main to prevent a memory leak.
			std::cout << std::this_thread::get_id() << " 999 final_suspend()" << std::endl; //MINE
			return {}; 
		}

		void return_void() { std::cout << std::this_thread::get_id() << " 888 return_void()" << std::endl; } //MINE
		void unhandled_exception() {}
	};
};

struct Awaiter {
	std::coroutine_handle<>* handle_out;

	bool await_ready() { 
		std::cout << std::this_thread::get_id() << " 444 await_ready()" << std::endl; //MINE
		return false; 
	}

	void await_suspend(std::coroutine_handle<> h) { 
		std::cout << std::this_thread::get_id() << " 555 await_suspend()" << std::endl; //MINE
		*handle_out = h; 
	}

	void await_resume() { std::cout << std::this_thread::get_id() << " 777 await_resume()" << std::endl; } //MINE
};

ReturnObject counter(std::coroutine_handle<>* handle) {
	Awaiter awaiter{handle};

	//ORIG for (unsigned i = 0; ; ++i) { //MINE: Comment this out to call final_suspend() to print 999.
	for (unsigned i = 0; i < 3; ++i) { //MINE This calls final_suspend() and prints 999.
		std::cout << '\n' << std::this_thread::get_id() << " 333 counter: " << i << std::endl;
		co_await awaiter;
	}
}

int main() {
	print_file_line();

	std::coroutine_handle<> h;
	counter(&h);

	for (int i = 0; i < 3; ++i) {
		std::cout << '\n' << std::this_thread::get_id() << " 666 main: resuming" << std::endl;
		h();
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
			std::cout << std::this_thread::get_id() << " 999 final_suspend()" << std::endl; //MINE
			return {};
```

## Why `std::suspend_always` leaks here

`std::suspend_always` suspends at the final point. The frame stays allocated. In this sample, `h.destroy()` is commented out:

```67:67:c:\_\rpw\C++\Examples\C++20 Coroutines\03-1\03-1.cpp
	//ORIG h.destroy(); //MINE: Comment this out to call final_suspend() to print 999.
```

So nothing ever frees the frame → leak.

## Rule of thumb

| `final_suspend` returns | Frame lifetime |
|---|---|
| `suspend_never` | Destroyed automatically when the coroutine finishes |
| `suspend_always` | Kept until you call `destroy()` (or another owner does) |

`suspend_always` is common when a caller still needs the handle after completion (read a result, join, etc.). Fire-and-forget style (like this example) often uses `suspend_never` so cleanup is automatic — but then the handle must not be used after the final resume.
*/