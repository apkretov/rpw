#ifndef MINE // demo_textbook_4_21_nonblocking_async_backend

/*
Textbook 4.21 claim:
Backend should return futures that become ready WITHOUT blocking a worker thread
while waiting for network/DB. Continuations + future-unwrapping keep the chain async.

It shows the textbook 4.21 baseline:
A) UI still free during login
B) Blocking backend chain : high peak blocked threads
C) Non - blocking async backend : `peak threads blocked waiting = 1` (one IO thread multiplexes waits)
*/

#include <atomic>
#include <chrono>
#include <future>
#include <print>
#include <string>
#include <thread>
#include <vector>
#include "../experimental/future.h"
#include "../../stdafx.h"
#include "4.4.4.1.5.h"

static long authenticate_blocking(std::string const&) {
	note_blocked(+1);
	std::this_thread::sleep_for(80ms);
	note_blocked(-1);
	return 42;
}

static long request_info_blocking(long id) {
	note_blocked(+1);
	std::this_thread::sleep_for(80ms);
	note_blocked(-1);
	return id;
}

static std::experimental::future<void> process_login_blocking_chain(std::string user) { // Listing 4.20-like: continuations + blocking backend calls.
	return std::experimental::future<long>(
		std::async(std::launch::async, [user] { return authenticate_blocking(user); }))
		.then([](std::experimental::future<long> id) {
			return request_info_blocking(id.get()); // still blocking inside continuation thread
		})
		.then([](std::experimental::future<long> info) { info.get(); });
}

static std::experimental::future<void> process_login_4_21(non_blocking_backend& backend, std::string user) { // Listing 4.21-like: async backend + future-unwrapping.
	return backend.async_authenticate(user)
		.then([&backend](std::experimental::future<long> id) {
			return backend.async_request_info(id.get()); // returns future<long> — Continuations TS unwraps to future<long>
		})
		.then([](std::experimental::future<long> info) {
			info.get(); // update_display; must wait for unwrapped future
		});
}

static std::future<void> process_login_4_21_non_continuation_TS(non_blocking_backend& backend, std::string user) {
	return std::async(std::launch::async, [&backend, user = std::move(user)] {
		long id = backend.async_authenticate(user).get();   // wait for auth
		long info = backend.async_request_info(id).get();  // wait for info
		(void)info; // update_display(info);
	});
}

static void ui_pump(std::chrono::milliseconds budget) {
	auto end = Steady::now() + budget;
	int frames = 0;
	while (Steady::now() < end) {
		++frames;
		std::this_thread::sleep_for(16ms);
	}
	std::println("UI frames rendered during waits: {}", frames);
}

int main() {
	print_file_line();

	std::println("=== Textbook point for Listing 4.21 ===");
	std::println("Async backend futures become ready without one blocked thread per wait.\n");

	constexpr int N = 40;
	non_blocking_backend backend;

	std::println("-- A) UI stays free while 4.21-style login runs --");
	{
		#ifndef CONTINUATION_TS // See the note about Continuation TS .then vs. standard version below.
		auto login = process_login_4_21(backend, "alice");
		#else //NON_CONTINUATION_TS
		auto login = process_login_4_21_non_continuation_TS(backend, "alice");
		#endif //NON_CONTINUATION_TS
		ui_pump(50ms); //ORIG ui_pump(200ms)
		{
			LogDuration ld("login.wait after ui_pump(50ms): adjust it vs. ORIG ui_pump(200ms) to measure the effect");
			login.wait();
			
		}
		std::println("login finished\n");
	}

	std::println("-- B) Many logins with BLOCKING backend in continuations --");
	{
		peak_blocked = 0;
		std::vector<std::experimental::future<void>> all;
		all.reserve(N);
		auto t0 = Steady::now();
		for (int i = 0; i < N; ++i)
			all.push_back(process_login_blocking_chain("user" + std::to_string(i)));
		for (auto& f : all)
			f.wait();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count();
		std::println("users = {}", N);
		std::println("wall time = {} ms", ms);
		std::println("peak threads blocked waiting = {}", peak_blocked.load());
		std::println("(many workers stuck in sleep/wait)\n");
	}

	std::println("-- C) Many logins with NON-BLOCKING async backend (Listing 4.21 idea) --");
	{
		peak_blocked = 0;
		std::vector<std::experimental::future<void>> all;
		all.reserve(N);
		auto t0 = Steady::now();
		for (int i = 0; i < N; ++i)
			all.push_back(process_login_4_21(backend, "user" + std::to_string(i)));
		for (auto& f : all)
			f.wait();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count();
		std::println("users = {}", N);
		std::println("wall time = {} ms", ms);
		std::println("peak threads blocked waiting = {}", peak_blocked.load());
		std::println("Textbook: waits are multiplexed; peak blocked stays near 1 IO thread.");
		std::println("Also: .then that returns a future is unwrapped (no future<future<T>>).");
	}
	return 0;
}
#endif

/*
The note about Continuation TS .then vs. standard version

---

**User**

Explain how the .then-magic works at a high level, without going into the code. That’s why I asked for a non-Continuation TS version in standard C++. If I still don’t understand it, I’ll examine the experimental future.h implementation.

---

**Cursor**

### What `.then` is doing

You attach a **follow-up function** to a future: “when this result is ready, run this next.”

You don’t sit on that future with `.get()` in the function that *builds* the chain. You return another future that becomes ready when the whole chain finishes. The UI (or `main`) can keep working and only `.wait()` at the end if it needs to.

### The “magic” in one idea

**Blocking style:** a thread owns the wait.
`get()` means “this thread sleeps here until the answer arrives.”

**Continuation style:** the *operation* owns the wait.
When the answer arrives, the runtime says “now run the next function.” The thread that kicked off the chain is not required to stay parked for that wait.

So the chain reads like sequential steps, but each step is “schedule what comes after,” not “block until done.”

### Why unwrapping matters

If step 2 itself returns a future (another async call), a naive chain would give you a future-of-a-future.

Continuations TS **unwraps** that: the outer future stays pending until the *inner* async work finishes, then carries the real value forward. That’s why

`async_authenticate → async_request_info → update_display`

can look like one flat pipeline instead of nested futures.

### Compared to your standard version

Your non-TS version is honest standard C++:

- start a worker
- `.get()` auth
- `.get()` info

That worker **is** the waiter for both IO waits.

`.then` is meant so those waits don’t need a dedicated parked composer thread; completion of one step triggers the next. (A production runtime usually does that via an executor/pool. Your teaching header approximates the *API*; you can ignore that until you open `future.h`.)

### Mental picture

```text
Blocking:     [thread] ----sleep on get----> work ----sleep on get----> done

.then:        start chain, return future
			  ... later, auth completes → run next step
			  ... later, info completes → run next step
			  final future becomes ready
```

Same end result for the caller; different place where the waiting lives.

---

**User**

'Continuation style: the operation owns the wait.
When the answer arrives, the runtime says “now run the next function.”':

Okay, this is becoming clearer. Let’s continue discussing it at a high level; otherwise, I’ll have to delve into the code for this specific part.

What I want to understand is: how exactly does the runtime know when to say, “Now run the next function”? What mechanisms does it use? Is it a condition variable or something similar, or are deeper operating-system mechanisms involved? What exactly is happening here?

This is the key point for me. I understand how waiting and condition variables work internally, but I don’t understand how the runtime knows when to proceed to the next task.

---

**Cursor**

### The short answer

The runtime does **not** magically discover that work is done.
Something that finished the operation **explicitly notifies shared state**: “the result is here.”
That notification is what causes “now run the next function.”

`.then` only **registers** the next function on that shared state beforehand.

---

### The two halves

**1. Registration (when you call `.then`)**
You store a callback on the future’s shared state:

> “When this becomes ready, run `F`.”

Nothing runs yet. You’re just leaving instructions.

**2. Completion (when the answer arrives)**
Whoever produces the result — in your demo, the IO thread calling `set_value` — does roughly:

> write the value into shared state → mark ready → if a continuation is registered, schedule/run it

That completion call is the trigger. No separate oracle watches the universe.

---

### What mechanism is that, concretely?

At the library level it’s the same family of ideas as a condition variable, but the *payload* is richer:

| Familiar CV pattern | Continuation shared state |
|---|---|
| wait until predicate | wait until future ready *(blocking `.get`)* |
| `notify` wakes waiters | completion runs/schedules registered `.then` callbacks |
| mutex protects the flag | mutex/atomics protect shared state |

So yes: often it’s **mutex + condition variable / atomic + wait**, or an equivalent.

Blocking `.get()`: completion does “wake the sleeper.”
Continuation style: completion does “enqueue/run the callback” (and may also wake someone if anyone called `.get()`/`.wait()`).

Same event (“ready”), different consumer.

---

### Where the OS comes in

Depends what you’re waiting *for*:

- **Your teaching demo:** user-space only. The IO thread finishes `sleep_until`, then `set_value`. That user-space call is the signal. No special OS “future ready” API.
- **Real network/disk async:** the OS signals I/O completion (IOCP, epoll/io_uring, kqueue, etc.). A reactor/proactor thread picks that up and then calls into the same kind of shared-state completion (`set_value` / invoke continuation).
- **Thread pool:** completion might only **enqueue** the continuation; a pool worker actually runs it.

So: OS mechanisms deliver *I/O done*; the future/promise runtime turns that into *shared state ready → run next*.

---

### Picture

```text
.then(F)     →  attach F to shared state

... later ...

producer: set_value(x)
			→  store x, mark ready
			→  wake .get() waiters  and/or  schedule F
```

The runtime “knows” because **the producer told it**, through the promise/shared-state completion path — not because it polled, and not because `.then` itself waits.

---

### Tie-back to what you already know

You already understand: wait on CV ↔ notify.

Continuations are: **register callback** ↔ **notify by running/scheduling that callback** when `set_value` (or I/O completion → `set_value`) happens.

If you later open `future.h`, look for that pairing: where `.then` stores work, and where readiness causes that work to run. That’s the whole trick.

---

**User**

"If you later open future.h, look for that pairing: where .then stores work, and where readiness causes that work to run. That’s the whole trick.":
Show me this trick in the code and explain it in full detail.

---

**Cursor**

I'll walk through your teaching `future.h` in detail — including where it matches the Continuations model and where it uses a simpler stand-in.

Important upfront: **your teaching `future.h` does not store the continuation on the promise and fire it from `set_value`.**
It approximates Continuations TS with a simpler trick: **spawn a helper thread that blocks until ready, then runs your function.**

The “ready” signal still exists — it comes from standard `std::promise` / `std::future` inside.

---

### Ideal Continuations TS pairing (what I meant conceptually)

```text
.then(F)     → store F on shared state
set_value(x) → mark ready → if F stored, schedule/run F
```

Your header’s `promise::set_value` does **not** look for a continuation:

```261:262:c:\_\rpw\C++\Examples\C++ Concurrency in Action\experimental\future.h
void set_value(const T& value) { inner.set_value(value); }
void set_value(T&& value) { inner.set_value(std::move(value)); }
```

It only forwards to `std::promise`. So the textbook callback-on-completion path is **not** implemented here.

---

### What your teaching `.then` actually does

```52:76:c:\_\rpw\C++\Examples\C++ Concurrency in Action\experimental\future.h
auto then(F&& func) {
	using U = std::invoke_result_t<std::decay_t<F>, future>;
	std::future<T> moved = std::move(inner);   // (1) take ownership of antecedent

	if constexpr (detail::is_experimental_future_v<U>) {  // unwrap path
		std::promise<R> p;
		auto result = future<R>(p.get_future()); // (2) future returned to caller NOW
		std::thread([p = ..., f = ..., moved = ...]() mutable {
			future self(std::move(moved));
			U nested = f(std::move(self));       // (3) run your lambda (often blocks in .get())
			p.set_value(nested.get());           // (4) unwrap: wait for nested future, then complete result
		}).detach();                             // (5) helper thread lives on its own
		return result;
	} else {
		// non-unwrap: run f, set_value(f(...))
	}
}
```

Split into the two roles:

| Role | In this code |
|---|---|
| “Store the work” | Capture `f` (+ antecedent future) into a **new detached thread** |
| “Know when to run / proceed” | That thread blocks inside `.get()` on standard shared state; producer’s `set_value` wakes it |

So the pairing is:

```text
.then(F)
  → start thread holding F and antecedent future
  → return a new future immediately

producer set_value
  → wakes whoever is blocked on antecedent .get()
  → that is the helper thread
  → helper runs F, then completes the returned future
```

---

### Where “ready” is detected (the real wake-up)

Your experimental types wrap standard ones:

- `experimental::future` holds `std::future`
- `experimental::promise` holds `std::promise`

When the backend does `ev.prom.set_value(...)`, that hits `std::promise::set_value`, which:

1. writes the value into the shared state
2. marks it ready
3. wakes waiters (internally: mutex/CV or platform wait — same family you already know)

Your helper thread becomes a waiter when it (or your lambda) calls `.get()` on that future.

**Nothing polls.** Readiness is still “producer notified shared state.”

---

### Full trace of your login chain

```cpp
backend.async_authenticate(user)
  .then([&](future<long> id) {
	  return backend.async_request_info(id.get());  // returns future → UNWRAP path
  })
  .then([](future<long> info) {
	  info.get();  // returns void → non-unwrap path
  });
```

#### Step A — authenticate enqueued

- Promise A + future A created
- Promise A queued; future A returned
- Caller immediately calls `.then(...)` on future A

#### Step B — first `.then` (unwrap)

1. Move future A into `moved`
2. Create promise/future B (what the next `.then` will see)
3. Detach **thread T1** with lambda + future A
4. Return future B to the chain **without waiting**

T1 runs:

```text
id.get()                     // blocks until IO thread set_value on promise A
async_request_info(...)      // enqueue promise C, get future C immediately
nested.get()                 // blocks until IO thread set_value on promise C
p.set_value(...)             // completes future B
```

So T1 is parked across both waits. The “runtime says run next” here means: **T1 was sleeping in `.get()`; `set_value` woke it; it continued the lambda.**

#### Step C — second `.then`

1. Takes future B
2. Detaches **thread T2**
3. Returns future D (`future<void>`) to `main` / `login.wait()`

T2 runs:

```text
info.get()   // blocks until T1 did p.set_value on future B
			 // then "update_display"
			 // completes future D
```

#### Step D — IO thread (the real producer)

```text
sleep_until → prom.set_value
```

That is the only place authenticity/info data is produced. It does **not** call your continuation by name; it only completes shared state. Helper threads blocked on `.get()` are what resume.

---

### Diagram of *this* implementation

```text
Caller thread
  async_authenticate → future A
  .then(F1)  → spawn T1, return future B
  .then(F2)  → spawn T2, return future D
  ... later login.wait() on D

IO thread
  set_value(A) ──wakes──► T1 in id.get()
						  T1 enqueues request_info
  set_value(C) ──wakes──► T1 in nested.get()
						  T1 set_value(B)
			  ──wakes──► T2 in info.get()
						  T2 completes D
			  ──wakes──► login.wait()
```

---

### Ideal vs your teaching stand-in

```text
Ideal Continuations TS
  .then stores F on shared state
  set_value runs/schedules F   ← no thread waiting beforehand

Your future.h
  .then starts a thread that will .get() then run F
  set_value only wakes that .get()
```

Same **observable API** for the textbook listings (chain + unwrap + return a future).
Different **mechanism**: register-and-fire vs **waiter thread that blocks on standard readiness**.

---

### Bottom line

In your code, the trick is:

1. **`.then`** packages the next function into a detached helper and returns a new future immediately.
2. **Readiness** is still normal promise/future shared-state notification (`set_value` → wake `.get()`).
3. The helper’s `.get()` is how it “knows” to proceed; then it runs your function and `set_value`s the next future in the chain.

If you want the literal “continuation stored on the promise, invoked from `set_value`” design, that would be a different `future.h` — your current one deliberately fakes that with a blocking helper thread.
*/