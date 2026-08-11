#pragma once

#pragma region MINE

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <stop_token>
#include <string>
#include <thread>
#include <utility>
#include "../experimental/future.h"

using namespace std::chrono_literals;
using Steady = std::chrono::steady_clock;

inline std::atomic<int> blocked_waiting{0};
inline std::atomic<int> peak_blocked{0};

static void note_blocked(int delta) { // See the note about this function below.
	int cur = blocked_waiting.fetch_add(delta) + delta;
	int peak = peak_blocked.load();
	while (cur > peak && !peak_blocked.compare_exchange_weak(peak, cur)) { /*CAS loop*/ }
}

struct io_event {
	Steady::time_point when;
	std::experimental::promise<long> prom;
	long value;
};

class non_blocking_backend { // Tiny completion service: ONE thread waits; many requests stay non-blocking for callers.
public:
	non_blocking_backend() : thr([this](std::stop_token st) { run(st); }) {}
	~non_blocking_backend() { cv.notify_all(); }

	std::experimental::future<long> async_authenticate(std::string const&) { return enqueue_io_event(42); }
	std::experimental::future<long> async_request_info(long id) { return enqueue_io_event(id); }
private:
	std::mutex mx;
	std::condition_variable cv;
	std::queue<io_event> q;
	std::jthread thr;

	void run(std::stop_token st) { // See the note about C++20 std::stop_token below.
		for (;;) {
			std::unique_lock lk(mx);
			cv.wait(lk, [&] { return st.stop_requested() || !q.empty(); }); // See the note about the cv.wait below.
			if (st.stop_requested() && q.empty())
				return;

			io_event ev = std::move(q.front());
			q.pop();
			lk.unlock();

			note_blocked(+1); 
			std::this_thread::sleep_until(ev.when); // Simulates network/DB wait // Only this single IO thread blocks for sleep_until — not one thread per request.  // See the note about the comment below.
			note_blocked(-1);
			ev.prom.set_value(ev.value);
		}
	}

	std::experimental::future<long> enqueue_io_event(long param) { // Returns immediately; no per-request worker thread sleeps for the IO wait.
		std::experimental::promise<long> p;
		auto fut = p.get_future();
		{
			std::scoped_lock lk(mx);
			q.emplace(Steady::now() + 80ms, std::move(p), param);
		}
		cv.notify_one(); // See the note about the notify_one below.
		return fut;
	}
};
#pragma endregion //MINE

/*
The note about note_blocked

**User**

@4.4.4.1.5.cpp:34-39
Okay, I understand how the individual atomic operations prevent race conditions. But the function has three lines, and another thread can change the variables between them. I get how a mutex helps, but I don’t see how it prevents race conditions across those lines.

---

**Cursor**

You’re right that another thread can run between those lines. A mutex would stop that; this code does **not**. It stays correct by tolerating interleaving, not by preventing it.

### What a mutex buys you

With a mutex, the whole body is one critical section:

```text
lock
  blocked += delta
  if (blocked > peak) peak = blocked
unlock
```

No other thread can touch those variables in the middle, so a plain check-then-assign is fine.

### What this code buys you instead

It does **not** keep `blocked_waiting` and `peak_blocked` consistent as one snapshot across all three lines. It only maintains a weaker, still-useful invariant:

- `blocked_waiting` is always updated correctly (one atomic RMW at a time).
- `peak_blocked` only ever moves **up**, and eventually reflects the highest value any thread observed right after its own update.

Interleaving between lines is expected; the CAS loop is what makes that safe.

### Walk through the three lines

**Line 1:** `cur = blocked_waiting.fetch_add(delta) + delta`

This is the only update to the live counter. After this, `cur` is a **local copy** of “count after my change.” Another thread may change `blocked_waiting` immediately afterward. That does not invalidate `cur` — `cur` is just “what I saw after my update,” and that is enough for peak tracking.

**Line 2:** `peak = peak_blocked.load()`

This may already be stale by the next line. That’s fine; the next step detects staleness.

**Lines 3–4:** CAS loop

“If my `cur` is bigger than the peak I loaded, try to store `cur`. If someone else changed peak in between, reload and retry (or stop if I’m no longer bigger).”

So the race across lines is not eliminated; it is **detected and retried**.

### Concrete interleaving

Suppose peak is `4`.

1. Thread A: `fetch_add(+1)` → `cur = 5`, then gets preempted
2. Thread B: `fetch_add(+1)` → `cur = 6`, sets `peak_blocked = 6`
3. Thread A resumes: `cur > peak`? It loaded `peak = 4`, so it tries CAS(`4` → `5`)
4. CAS fails because peak is now `6`; `peak` is updated to `6`
5. Loop checks again: `5 > 6`? No → stop

Peak stays `6`. A never overwrites a higher peak with a lower one.

### The mental model shift

| Approach | Strategy |
|---|---|
| Mutex | “Nobody else may touch this while I work.” |
| This atomics code | “Others may touch it; I’ll publish my max carefully and retry if I lose the race.” |

So: atomics don’t make the **function** atomic. They make each shared update safe, and the CAS loop makes the multi-step “update the max” operation **lock-free and correct under contention**.

If you used plain `if (cur > peak) peak = cur` without CAS, that is exactly where the cross-line race would bite: A could store `5` after B already stored `6`.
*/

/*
The note about C++20 std::stop_token

Question

If std::jthread thr is joinable, isn’t thr.join() redundant? Or is it still recommended for clarity? What is a better SWE?

Answer

No—if a `std::jthread` is **joinable**, then `join()` is not redundant; it is exactly what waits for the thread to finish. The main difference is that `std::jthread`’s destructor will call `request_stop()` and then `join()` for you, so an explicit `join()` is usually only needed when you want deterministic shutdown **before** destruction.

## What is better SWE?

In your destructor, an explicit `thr.join()` is a reasonable software-engineering choice for **clarity**, because it makes the blocking shutdown point visible. However, with `std::jthread` you should usually also wire in stop support, so the thread can actually exit promptly instead of relying only on `stop` under your mutex.

A cleaner pattern is:

- use `std::jthread` for RAII shutdown.
- make the worker check `stop_token`.
- notify the condition variable on shutdown.
- call `join()` explicitly only if you want to document “this destructor waits here.”

## For your code

Your previous code worked, but it mixed two stop mechanisms:

- a manual `bool stop`.
- `std::jthread`’s built-in stop mechanism, which you are not using.

```cpp
class non_blocking_backend {
public:
	non_blocking_backend() : thr([this] { run(); }) {}

	~non_blocking_backend() {
		{
			std::scoped_lock lk(mx);
			stop = true;
		}
		cv.notify_all();
		thr.join();
	}
	...
private:
	void run() {
		for (;;) {
			std::unique_lock lk(mx);
			cv.wait(lk, [&] { return stop || !q.empty(); });
			if (stop && q.empty())
				return;
		...
	}
	...
	bool stop = false;
	...
};
```

A better shape is to let `jthread` own cancellation and keep the manual flag only if you truly need it.

If you keep the explicit `join()`, that is fine too, but then it is mostly for readability; functionally, `std::jthread` would already join in its destructor.

## Practical rule

- Use **explicit `join()`** when shutdown timing matters and you want the code to say so.
- Rely on **`jthread` destructor** when you want simple RAII and don’t need to spell out the wait.
- Prefer **`stop_token`** over a separate stop flag when using `std::jthread`.
*/

/*
// The note about the cv.wait

---

**User**

What is happening here  @4.4.4.1.5.cpp:82-86? Does the object’s initial initialization from the initializer list @4.4.4.1.5.cpp:48 suspend at the condition variable until the queue @4.4.4.1.5.cpp:85 gets its first item? If so, how does the queue get its first item if the entire class object initialization is suspended? I don’t understand this. Explain.

---

**Cursor**

I’ll check the constructor and `run()` together so we can separate “object construction finishes” from “the worker thread blocks on `cv.wait`.”

No — **object construction is not suspended**. Only the **worker thread** blocks on `cv.wait`. Those are two different threads of execution.

### What the constructor actually does

```48:48:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4.1\4.4.4.1.5.cpp
non_blocking_backend() : thr([this] { run(); }) {}
```

On the thread that creates `NonBlockingBackend`:

1. Members are initialized in declaration order (`mx`, `cv`, `q`, `stop`, then `thr`).
2. Constructing `thr` **starts a second thread** that will call `run()`.
3. The constructor then finishes. The object is fully constructed and usable.

Starting `std::jthread` does **not** wait for `run()` to finish (or even to reach `cv.wait`). It just launches that work on another thread and returns.

### What the worker thread does

```82:87:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4.1\4.4.4.1.5.cpp
void run() {
	for (;;) {
		std::unique_lock lk(mx);
		cv.wait(lk, [&] { return st.stop_requested() || !q.empty(); });
		if (st.stop_requested() && q.empty())
			return;
```

This runs on the **IO thread** owned by `thr`. If the queue is empty and `stop` is false, that thread sleeps inside `cv.wait`. Meanwhile the constructing/calling thread is free to continue.

### How the queue gets its first item

Later, some other code (often the same thread that constructed the backend, or a continuation thread) calls:

```59:67:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4.1\4.4.4.1.5.cpp
std::experimental::future<long> async_authenticate(std::string const&) {
	...
	{
		std::scoped_lock lk(mx);
		q.emplace(...);
	}
	cv.notify_one();
	return fut;
}
```

That:

1. pushes an event into `q`
2. wakes the waiting worker with `cv.notify_one()`

So the worker can be waiting for work **while** the already-constructed object accepts work through its public methods.

### Timeline

```text
Caller thread                         Worker thread (thr)
─────────────────                     ───────────────────
construct non_blocking_backend
  init mx/cv/q/stop
  start thr ────────────────────────► run() starts
constructor returns                   cv.wait(...): sleep (q empty)
... later ...
async_authenticate()
  q.emplace(...)
  cv.notify_one() ──────────────────► wake up, pop event, process
```

### The misconception in one sentence

`cv.wait` suspends the **worker**, not the **object’s construction**. Construction only starts that worker; the queue is filled afterward by normal method calls on the live object.
*/

/*
The note about the notify_one

**User**

Why is this notification needed, if the line in the void run function:
cv.wait(lk, [&] { return st.stop_requested() || !q.empty(); });
wakes up without it?

---

**Cursor**

### What `cv.wait(lk, pred)` actually does

```cpp
cv.wait(lk, [&] { return st.stop_requested() || !q.empty(); });
```

is equivalent to:

```cpp
while (!(st.stop_requested() || !q.empty()))
	cv.wait(lk);   // sleep until notify / spurious wakeup
```

So there are two ways to leave that call:

1. **Already satisfied:** queue has work → return immediately, no sleep, notify not involved
2. **Was sleeping:** predicate was false → must be woken by `notify_*` (or a rare spurious wakeup, which you must not rely on)

### Short rule

| Situation																	| Needs `notify_one`?			|
|---																		|---							|
| Worker not waiting yet; queue already non-empty when it reaches `wait`	| No (predicate short-circuits)	|
| Worker already sleeping in `wait`											| **Yes**						|

`notify_one` is not “what makes the predicate true.”
Pushing into `q` makes the predicate true; `notify_one` is how you wake a thread that went to sleep **before** that happened.

*/

/*
The note about the comment

---

**User**

Explain this comment. I don't understand it fully.

---

**Cursor**

The comment is contrasting this design with the **blocking** backend (section B in `main`).

### Blocking model (bad for this metric)

In `authenticate_blocking` / `request_info_blocking`, **each request’s worker thread** does:

```25:28:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4.1\4.4.4.1.5.cpp
note_blocked(+1);
std::this_thread::sleep_for(80ms);  // simulates network/DB wait
note_blocked(-1);
```

Launch 40 logins → up to ~40 threads each sitting in `sleep_for`.
`peak_blocked` climbs toward “one blocked thread per in-flight wait.”

### Non-blocking model (this comment)

Here, callers only enqueue work and get a future back. They do **not** sleep for the IO. The simulated wait happens only here:

```
note_blocked(+1);
std::this_thread::sleep_until(ev.when);
note_blocked(-1);
```

That runs on the **one** backend worker (`thr`). Even with many queued requests, at most **one** thread is counted as blocked while sleeping for an IO deadline. Other requests wait in `q`, not on their own sleeping threads.

### What the comment means in plain words

> “Yes, something still blocks for the wait — but it’s this shared IO thread, not a dedicated blocked thread for every login/request.”

That’s the Listing 4.21 point your demo prints: peak blocked stays near **1**, instead of scaling with concurrent users.
*/