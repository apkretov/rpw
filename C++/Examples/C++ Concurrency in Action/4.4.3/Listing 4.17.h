#pragma once

#include "../experimental/future.h"
#include <algorithm>
#include <exception>
#include <thread>
#include <type_traits>
#include <utility>

template<typename Func>
std::experimental::future<decltype(std::declval<Func>()())> spawn_async(Func&& func) { // See the note below on spawn_async vs. simple_async.
	std::experimental::promise<decltype(std::declval<Func>()())> p; // See the note below on std::declval.
	auto res = p.get_future();
	
	std::thread t([p = std::move(p), f = std::decay_t<Func>(func)]() mutable {
		try {
			p.set_value_at_thread_exit(f()); // See the note below on std::promise::set_value_at_thread_exit.
		}
		catch (...) {
			p.set_exception_at_thread_exit(std::current_exception());
		}
	});
	t.detach();
	return res;
}

/* 
The note on spawn_async vs. simple_async
 
# Spawn async function comparison
_Exported on 7/27/2026 at 17:19:52 GMT+3 from Cursor (3.13.10)_

---

**User**

How similar or different is the spawn_async function in @4.4.3/Listing 4.17.h  from simple_async in @4.4.1.2/simple_async.h ?

---

**Cursor**

I'll read both headers and compare `spawn_async` with `simple_async`.

Checking the underlying future/promise types they use for a fuller comparison.

They solve the same problem — run a callable on a new detached thread and hand back a future — but they differ in API shape, machinery, and a few concurrency details.

### Same idea
Both:
1. Accept a callable
2. Create a promise/future pair (directly or via `packaged_task`)
3. Start a background thread that runs the work
4. Detach the thread
5. Return the future to the caller

So both are “always launch a new thread” helpers, like `std::async(std::launch::async, ...)`.

### Main differences

| | `simple_async` | `spawn_async` |
|---|---|---|
| **Args** | `F&&` + `Args&&...` (bind with `std::bind_front`) | Only `Func&&` (no extra args) |
| **Result type** | `simple_future<R>` via `simple_packaged_task` | `std::experimental::future<…>` via `promise` |
| **How result is set** | Task runs and fills its internal promise | Thread calls `set_value_at_thread_exit` / `set_exception_at_thread_exit` |
| **Thread type** | `std::jthread` then `detach()` | `std::thread` then `detach()` |
| **Exception handling** | Inside `packaged_task`’s `operator()` | Explicit `try`/`catch` in the lambda |
| **Return-type deduction** | `std::invoke_result_t<F, Args...>` | `decltype(std::declval<Func>()())` |

### Notable behavioral nuance

`spawn_async` uses `*_at_thread_exit`. The future becomes ready when the worker thread finishes (thread-local destructors run), not immediately when `set_value` would fire. That matters if thread-locals (or other exit-time cleanup) must run before waiters see the result — which is why Listing 4.17 uses that form in the continuations chapter.

`simple_async` relies on `simple_packaged_task`, which typically sets the promise as soon as the callable returns (or throws), so readiness can happen slightly earlier relative to thread teardown.

### Bottom line

Conceptually they are very similar “fire-and-forget async” wrappers. Practically, `simple_async` is a richer, home-grown `std::async`-style helper (args + `packaged_task` + `simple_future`), while `spawn_async` is a thinner book listing aimed at experimental futures and delayed readiness via `set_*_at_thread_exit`.

---

**User**

1. "which is why Listing 4.17 uses that form in the continuations chapter":
I didn't understand why Listing 4.17 uses that form in the continuations chapter.

2. Another agent explained @4.4.3/Listing 4.17.h as follows below.
2.1. Is it safer than @4.4.1.2/simple_async.h?
2.2. Is it slower due to the extra strip-and-copy step?

Another agent's explanation:

`f = std::decay_t<Func>(func)` means: make a local copy of `func`, but first convert `Func` to its **decayed** form.

## What `std::decay_t<Func>` does

`std::decay_t<T>` removes things like:

- references,
- `const` and `volatile`,
- array-to-pointer and function-to-pointer adjustments.

So if `Func` is a lambda type, a function pointer, or some callable object type, `std::decay_t<Func>` gives a suitable concrete type to store by value. [en.cppreference](https://en.cppreference.com/cpp/types/decay)

## Why it is used here

In this lambda:

```cpp
[p = std::move(p), f = std::decay_t<Func>(func)]() mutable {
```

`f` is a **by-value capture** of the callable. That matters because the thread may outlive the original `func` parameter. Capturing by value makes the callable safe to use later inside the detached thread.

## Why not just write `f = func`?

Because `func` is a forwarding reference:

```cpp
Func&& func
```

If you pass an lvalue, `Func` may be deduced as a reference type. `std::decay_t<Func>` strips that reference away, so `f` becomes an actual stored object instead of something awkward like a reference type. This is the same general idea used by `std::async`, which decays its callable and arguments before storing them. [reddit](https://www.reddit.com/r/cpp_questions/comments/ccib8o/why_use_stddecay_t_in_stdasync/)

## In plain language

It means:

- take whatever callable the user passed,
- normalize its type,
- copy it into `f`,
- then use `f()` later inside the new thread.

So this part is basically “store the callable safely for asynchronous execution.”


---

**Cursor**

I'll check the surrounding listing/continuation context and how `simple_async` stores its callable so the safety and cost answers are precise.

### 1. Why `*_at_thread_exit`?

My earlier wording was easy to misread. Continuations are not what *requires* that API; **detaching the worker thread** is.

With plain `set_value` / `set_exception`:
1. `f()` finishes
2. the shared state becomes **ready immediately**
3. only then do remaining locals / `thread_local` objects destroy as the thread winds down

So a waiter — or a `.then(...)` continuation that starts as soon as the future is ready — can run **while the worker is still tearing down**. That is the race `*_at_thread_exit` closes: store the result now, make the future ready **only after** thread-locals are destroyed and the thread is exiting.

In the book, Listing 4.17 is the “async” primitive used when chaining `.then(...)`. Continuations just make the bug more likely to show up, because readiness can immediately schedule more work.

---

### 2.1 Safer than `simple_async`?

**For dangling the original callable argument:** no meaningful difference. Both keep an owned copy/move of the work for the background thread.

- `spawn_async`: by-value capture via `std::decay_t<Func>(...)`
- `simple_async`: `bind_front` + move into `simple_packaged_task` / `std::function`

The other agent’s explanation of `decay` is right for `spawn_async`; it does not make `spawn_async` safer than `simple_async` on that axis.

**For detached-thread / TLS teardown:** yes — `spawn_async` is safer because of `set_*_at_thread_exit`. Your `simple_packaged_task` uses ordinary `set_value` / `set_exception`, so readiness can precede thread exit cleanup.

**Small caveat on the book snippet:** `f = std::decay_t<Func>(func)` does not perfect-forward; `func` is a named parameter (an lvalue), so you typically **copy** even when the caller passed a temporary. `simple_async`’s `std::forward` is better on that point.

---

### 2.2 Slower due to “strip-and-copy”?

No. `std::decay_t` is a **compile-time** type tweak (drop refs/`const`/etc.). There is no runtime “strip” pass.

The runtime cost is just constructing the stored callable into the lambda — the same kind of ownership both helpers need. If anything, `simple_async` is more likely to be heavier because it type-erases into `std::function`, which can allocate.
*/

/*
The note on std::declval

When writing template libraries, you often need to determine the return type of a member function or operator based on a template parameter.
However, you cannot directly call member functions without an instance of that class. 
If the template type 
	1) has no default constructor,
	2) private constructors, 
	3) or is an abstract class, 
creating a mock instance T() will cause a compilation error. 
std::declval<T>() solves this by giving you a "phantom" instance to call methods on within compiler-only checks.

#include <iostream>
#include <numbers>
#include <utility>
#include <type_traits>

struct NonDefaultConstructible { // No default constructor available
	explicit NonDefaultConstructible(int) {}
	//ORIG double serialize() const { return 42.0; }
	virtual double serialize() const = 0; //MINE // abstract class
};

template <typename T>
using SerializeResult_t = decltype(std::declval<T>().serialize()); // Template alias to deduce the return type of serialize() for any type T

#pragma region MINE
class DefaultConstructible {
public:
	explicit DefaultConstructible(int) {}
	double serialize() const { return 42.0; }
	//ERR virtual double serialize() const = 0; // abstract class
//ERR private: // private default constructor
	DefaultConstructible() = default;
};

template <typename U>
using DC_SerializeResult_t = decltype(U{}.serialize());
#pragma endregion //MINE

int main() {
	SerializeResult_t<NonDefaultConstructible> value = std::numbers::pi; // This works perfectly even though NonDefaultConstructible cannot be initialized via ()
	std::cout << std::is_same_v<decltype(value), double> << '\n'; // Outputs: 1 (true)
	std::cout << typeid(DC_SerializeResult_t <DefaultConstructible>).name() << '\n'; //MINE Outputs: double
}
*/

/*
The note on std::promise::set_value_at_thread_exit.
 
 * **Core Question:** 
 How does a waiter know when the producer thread ends, making the asynchronous result available? 
 
 * **Key Mechanism:** 
 The connection is handled automatically by the runtime environment, not explicitly by user code. 
 
 * **The Workflow:** 
 1. When you call `set_value_at_thread_exit`, the value is stored in the `shared_state`, but the `standard` 'ready' flag is not set immediately, and waiters remain blocked. 
 2. The standard library registers a hook to be executed during the current thread's termination process (using thread-local storage destruction or similar mechanisms). 
 3. When the thread exits, this registered hook fires. 
 4. The hook marks the `shared_state` as 'ready' and notifies waiting futures via synchronization primitives (e.g., condition variables or futexes). 
 
 * **Outcome for User:** 
 Waiters block until the producer thread fully terminates, ensuring any thread-local resources are cleaned up before the result is consumed. You can rely on standard library implementations to handle this linkage.


 * **set_value vs. std::promise::set_value_at_thread_exit:**
 The standard `set_value` makes the result ready immediately, so a waiting future can proceed as soon as the call finishes. You use this when there's no critical cleanup depending on the thread exiting or when you want the lowest possible latency. 
 `set_value_at_thread_exit`, on the other hand, holds off on making the result ready until the thread exits. This is essential when you need specific destruction order, like releasing thread-local resources, before notifying the waiter.
 */