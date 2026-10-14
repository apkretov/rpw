#if 0

#include <iostream>
#include "05.h"
#include "../../stdafx.h"

Generator count_to(int n) {
	for (int i = 1; i <= n; ++i) {
		co_yield i;
	}
}

#ifdef MINE_PSEUDOCODE
Generator __compiler_count_to(int n_arg) { // Caller sees: auto gen = count_to(5);
	void* __frame = ::operator new(__builtin_coroutine_frame_size()); // 1. Allocate coroutine frame (stores promise, parameters like n, and local variables like i)
	auto& promise = *new (__frame) promise_type;

	int& n = *new (static_cast<void*>(/* frame offset for n */)) int(n_arg); // Copy parameter into the coroutine frame

	Generator __return = promise.get_return_object(); // 2. Obtain the return object immediately via get_return_object()

	auto __initial_awaiter = promise.initial_suspend(); // 3. Begin coroutine execution, start at initial suspend point // Returns std::suspend_always
	if (!__initial_awaiter.await_ready()) {
		auto __handle = std::coroutine_handle<promise_type>::from_promise(promise);
		__initial_awaiter.await_suspend(__handle);
		return __return; // Ramp function returns the Generator object here and suspends
	}

	int& i = *new (static_cast<void*>(/* frame offset for i */)) int(); // 4. Run the coroutine body // Local variable 'i' is stored in the coroutine frame

	for (i = 1; i <= n; ++i) {
		auto __awaiter = promise.yield_value(i); // co_yield i; desugars into: co_await promise.yield_value(i); // Sets current_value = i, returns std::suspend_always

		if (!__awaiter.await_ready()) { // false for std::suspend_always
			auto __handle = std::coroutine_handle<promise_type>::from_promise(promise);
			__awaiter.await_suspend(__handle);
			return __return; // Suspends execution and returns control back to `gen.next()`
		}
		__awaiter.await_resume(); // Runs when resumed (noop for suspend_always)
	}

	promise.return_void(); // 5. Reached the end of the coroutine body

	auto __final_awaiter = promise.final_suspend(); // 6. Final suspend point // Returns std::suspend_always
	if (!__final_awaiter.await_ready()) {
		auto __handle = std::coroutine_handle<promise_type>::from_promise(promise);
		__final_awaiter.await_suspend(__handle);
	}

	// Note: The coroutine frame remains allocated until `gen` goes out of scope and its destructor explicitly invokes `handle.destroy()`.
}
#endif // MINE_PSEUDOCODE

int main() {
	print_file_line();

	auto gen = count_to(5);
	while (gen.next()) {
		std::cout << gen.value() << std::endl;
	}
}

/*
The note about done()

`handle.done()` tells you whether the coroutine has **finished executing**—more precisely, whether it is suspended at its *final suspend point* (`final_suspend()`). It returns `true` after the coroutine body has completed, and `false` while it is paused at `co_yield` or `initial_suspend()`. [en.cppreference](https://en.cppreference.com/cpp/coroutine/coroutine_handle/done)

## In your generator

```cpp
bool next() {
	if (!handle || handle.done())
		return false;
	handle.resume();
	return !handle.done();
}
```

- `!handle` checks whether the `Generator` owns a valid coroutine handle.
- `handle.done()` checks whether the generator has already run to completion.
- `handle.resume()` continues execution until the next `co_yield` or until the function ends.
- The final `return !handle.done();` means: “there is a new value only if the coroutine paused again at `co_yield`, rather than finishing.”

For `count_to(5)`, the sequence is:

| Step | What happens | `done()` |
|---|---|---|
| `count_to(5)` created | Suspended at `initial_suspend()` | `false` |
| First `next()` | Runs to `co_yield 1`, stores `1` | `false` |
| … | Values 2–5 are produced similarly | `false` |
| Sixth `next()` | Loop ends, `return_void()` runs, then suspends at `final_suspend()` | `true` |
| Next call | `next()` returns `false` immediately | `true` |

## Why `final_suspend()` matters

Your promise uses:

```cpp
std::suspend_always final_suspend() noexcept { return {}; }
```

So after the coroutine body finishes, it pauses at the final suspend point instead of immediately destroying itself. That is why `done()` becomes `true` and why your destructor can safely call `handle.destroy()` later. If `final_suspend()` returned `std::suspend_never`, the coroutine would destroy itself automatically, and `done()` would never report `true`.

## Important caveat

Calling `done()` is only meaningful for a coroutine that is currently **suspended**. Calling it on a handle that is executing, has already been destroyed, or does not refer to a coroutine is undefined behavior. In your code, `!handle` protects against a moved-from/null handle, and `done()` is called only before resuming or after a resume, so the usage is correct.

In short: `handle.done()` means **“the generator has no more work to do”**—it has reached its end, not merely paused to yield a value.
*/
#endif // 1
