#pragma once

#pragma region MINE

#include <atomic>
#include <chrono>

using namespace std::chrono_literals;
using Steady = std::chrono::steady_clock;

inline constexpr auto simulated_io_latency = 80ms; // Shared by blocking sleeps and Asio timers

inline std::atomic<int> blocked_waiting{0};
inline std::atomic<int> peak_blocked{0};
inline std::atomic<int> in_flight{0};
inline std::atomic<int> peak_in_flight{0};

static void note_peak(std::atomic<int>& counter, std::atomic<int>& peak, int delta) { // See the note about note_blocked below.
	int cur = counter.fetch_add(delta) + delta;
	int p = peak.load();
	while (cur > p && !peak.compare_exchange_weak(p, cur)) { /*CAS loop*/ }
}

static void note_blocked(int delta) { note_peak(blocked_waiting, peak_blocked, delta); }
static void note_in_flight(int delta) { note_peak(in_flight, peak_in_flight, delta); }

struct in_flight_guard { // Lives in the coroutine frame across co_await, so the count stays up for the whole timer wait.
	in_flight_guard() { note_in_flight(+1); }
	~in_flight_guard() { note_in_flight(-1); }
	in_flight_guard(in_flight_guard const&) = delete;
	in_flight_guard& operator=(in_flight_guard const&) = delete;
};
#pragma endregion //MINE

/*
The note about note_blocked

**User**

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

**Line 1:** `cur = counter.fetch_add(delta) + delta`

This is the only update to the live counter. After this, `cur` is a **local copy** of “count after my change.” Another thread may change the counter immediately afterward. That does not invalidate `cur` — `cur` is just “what I saw after my update,” and that is enough for peak tracking.

**Line 2:** `p = peak.load()`

This may already be stale by the next line. That’s fine; the next step detects staleness.

**Lines 3–4:** CAS loop

“If my `cur` is bigger than the peak I loaded, try to store `cur`. If someone else changed peak in between, reload and retry (or stop if I’m no longer bigger).”

So the race across lines is not eliminated; it is **detected and retried**.

### Concrete interleaving

Suppose peak is `4`.

1. Thread A: `fetch_add(+1)` → `cur = 5`, then gets preempted
2. Thread B: `fetch_add(+1)` → `cur = 6`, sets peak = `6`
3. Thread A resumes: `cur > peak`? It loaded `peak = 4`, so it tries CAS(`4` → `5`)
4. CAS fails because peak is now `6`; `p` is updated to `6`
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
