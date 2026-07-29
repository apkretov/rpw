#ifndef MINE // demo_parallel_many_requests

#define BENCHMARK_QUIET

#include <chrono>
#include <print>
#include <string>
#include <vector>
#include "4.4.4.h"
#include "../../stdafx.h"

namespace listing_4_18 {
#include "Listing 4.18.h"
}

namespace listing_4_19 {
#include "Listing 4.19.h"
}

namespace listing_4_20 {
#include "Listing 4.20.h"
}

namespace listing_4_21 {
#include "Listing 4.21.h"
}

static constexpr int user_count = 100;

template <typename Func>
static long long measure_ms(Func&& func) {
	auto const start = std::chrono::steady_clock::now();
	func();
	auto const end = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

static long long run_listing_4_18() {
	return measure_ms([] {
		for (int i = 0; i < user_count; ++i)
			listing_4_18::process_login("user" + std::to_string(i), "pwd");
	});
}

static long long run_listing_4_19() {
	return measure_ms([] {
		std::vector<std::future<void>> pending;
		pending.reserve(user_count);
		for (int i = 0; i < user_count; ++i)
			pending.push_back(listing_4_19::process_login("user" + std::to_string(i), "pwd"));
		for (auto& f : pending)
			f.wait();
	});
}

static long long run_listing_4_20() {
	return measure_ms([] {
		std::vector<std::experimental::future<void>> pending;
		pending.reserve(user_count);
		for (int i = 0; i < user_count; ++i)
			pending.push_back(listing_4_20::process_login("user" + std::to_string(i), "pwd"));
		for (auto& f : pending)
			f.wait();
	});
}

static long long run_listing_4_21() {
	return measure_ms([] {
		std::vector<std::experimental::future<void>> pending;
		pending.reserve(user_count);
		for (int i = 0; i < user_count; ++i)
			pending.push_back(listing_4_21::process_login("user" + std::to_string(i), "pwd"));
		for (auto& f : pending)
			f.wait();
	});
}

int main() {
	print_file_line();

	std::println("users = {}", user_count);

	auto const t418 = run_listing_4_18(); // See the note on the performance comparison below.
	auto const t419 = run_listing_4_19();
	auto const t420 = run_listing_4_20();
	auto const t421 = run_listing_4_21();

	std::println("Listing 4.18 sequential: {} ms", t418);
	std::println("Listing 4.19 std::async wrapper: {} ms", t419);
	std::println("Listing 4.20 continuations + blocking backend: {} ms", t420);
	std::println("Listing 4.21 async backend + continuations: {} ms", t421);

	if (t419 > 0)
		std::println("4.18 / 4.19 speedup: {:.2f}x", static_cast<double>(t418) / t419);
	if (t421 > 0)
		std::println("4.18 / 4.21 speedup: {:.2f}x", static_cast<double>(t418) / t421);

	return 0;
}

#endif

/*
The note on the performance comparison

---

**User**

1. Why is the performance difference so noticeable if both execute the same tasks? Is it due to parallel threading?
2. Why is Listing 4.19 so much slower than Listing 4.20, given that both run asynchronously?

users = 100
Listing 4.18 sequential: 3112 ms
Listing 4.19 std::async wrapper: 358 ms
Listing 4.20 continuations + blocking backend: 62 ms
Listing 4.21 async backend + continuations: 173 ms
4.18 / 4.19 speedup: 8.69x
4.18 / 4.21 speedup: 17.99x

---

**Cursor**

I'll check the listing implementations and your stubs so the explanation matches what your benchmark actually runs.

### 1. Why is the gap so large if the work is the same?

Yes — mainly **parallelism across users**, not “doing less work.”

| Listing | How 100 users run |
|---|---|
| **4.18** | One after another on the calling thread |
| **4.19 / 4.20 / 4.21** | Many logins in flight at once |

So total CPU/sleep work is similar, but **wall-clock time** differs:

- **4.18:** roughly `100 × (auth + info)`
- **Async variants:** roughly `~1 × (auth + info)` plus thread overhead

With your `2ms` sleeps, Windows timer coarseness often makes each `sleep_for(2ms)` closer to ~10–15ms. That fits your number well:

`100 users × 2 sleeps × ~15ms ≈ 3000ms` → your **3112 ms** for 4.18.

So the big win is: **overlap many independent logins**, not faster auth itself.

---

### 2. Why is 4.19 much slower than 4.20?

Both are “async,” but they are not the same shape.

**Listing 4.19** (one big async task per user):

```10:14:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4\Listing 4.19.h
	return std::async(std::launch::async, [=]() {
		try {
			user_id const id = backend.authenticate_user(username, password);
			user_data const info_to_display = backend.request_current_info(id);
			update_display(info_to_display);
```

- Starts **100** `std::async` tasks immediately
- Each task holds one thread for **both** sleeps end-to-end
- `std::async` has heavier machinery (shared state / packaged task) than a plain detached thread

**Listing 4.20** (chained steps):

```10:14:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4\Listing 4.20.h
	return spawn_async([=]() {
		return backend.authenticate_user(username, password);
	}).then([](std::experimental::future<user_id> id) {
		return backend.request_current_info(id.get());
	}).then([](std::experimental::future<user_data> info_to_display) {
```

- Uses `spawn_async` + `.then` (your teaching `future`)
- Work is split into stages; threads are created in waves, not always as one giant burst of long-lived tasks
- In practice here, that often means **less launch/scheduling contention** than 100 heavy `std::async` tasks

So 4.20 looking faster than 4.19 in *this* benchmark is mostly an **implementation/overhead effect**, not proof that continuations are magically faster than `std::async` in general.

---

### Bonus: why is 4.21 slower than 4.20 in your run?

Textbook intent of 4.21: backend returns futures so threads aren’t blocked on IO.

Your stand-in still does this:

```33:40:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4\4.4.4.h
	std::experimental::future<user_id> async_authenticate_user(...) const {
		return std::experimental::future<user_id>(std::async(
			std::launch::async, [=] { return authenticate_user(username, password); }));
	}
```

So 4.21 adds **extra async hops + future-unwrapping threads** on top of sleeps.
In a sleep-based demo, that can make 4.21 **slower** than 4.20 (your 173 ms vs 62 ms), even though the textbook story is about better scalability with real non-blocking IO.

---

**Bottom line**

1. **4.18 vs others:** same work, different overlap → parallel threading across users.
2. **4.19 vs 4.20:** both async, but 4.19 pays more for “100 fat `std::async` tasks”; 4.20’s staged `spawn_async`/`.then` path happens to be cheaper in this setup.
3. Treat these numbers as a teaching illustration of overlap/overhead, not a perfect ranking of the textbook designs under real async IO.

---

**User**

Explain this better:
"4.19 vs 4.20: both async, but 4.19 pays more for “100 fat std::async tasks”; 4.20’s staged spawn_async/.then path happens to be cheaper in this setup."

---

**Cursor**

Think in terms of **what one login looks like on the CPU/OS**, not “async vs async” as a label.

### Listing 4.19: one heavy worker per user

For each of 100 users, 4.19 does roughly:

1. Create an `std::async` task (fairly heavy: shared state, packaged work, thread startup).
2. That **one thread** stays alive and does:
   - sleep/auth
   - then sleep/info
   - then update
3. Only then is that task done.

So at launch time you suddenly ask the OS for **100 long-lived threads**, each carrying the **whole** login.

Cost drivers:

- expensive `std::async` setup × 100
- big burst of thread creation
- each thread is “fat”: it occupies a thread for the full auth+info duration

Wall time is roughly:

> slowest login ≈ auth + info
> **plus** a large “start 100 std::async workers” tax

That tax shows up strongly in your 358 ms.

---

### Listing 4.20: same login, but split into stages

For each user, 4.20 does:

1. `spawn_async`: thread runs **only auth**, then finishes.
2. `.then(...)`: later, another short thread runs **only info**.
3. `.then(...)`: later, another short thread runs **update**.

So work is staged:

```text
User A:  [auth] -----> [info] -----> [update]
User B:  [auth] -----> [info] -----> [update]
...
```

Many users still overlap, but each individual thread is shorter-lived and does less.

Also, stages are staggered:

- first wave: mostly auth threads
- later: info threads
- later: update threads

instead of “100 full login machines” all created as one fat batch.

In your teaching runtime, that path happens to have **less launch/scheduling overhead**, so total time drops to ~62 ms.

---

### Tiny analogy

- **4.19:** hire 100 workers, each must do job A then B then C before leaving.
- **4.20:** use a conveyor: one set does A, then hand off to B, then to C.

Same total work, different staffing pattern.
In this benchmark, hiring 100 “do-everything” `std::async` workers is the expensive part.

---

### Important caveat

This does **not** mean “continuations are always faster than `std::async`.”
Your result is about **this implementation + this sleep-based demo**:

- `std::async` overhead is high when launching many tasks
- your `.then` stand-in uses detached threads in stages
- sleeps are short, so overhead dominates useful work

So: both are asynchronous; 4.19 is slower here mainly because it pays a bigger **startup/concurrency tax** for 100 fat tasks, while 4.20 spreads the same login into cheaper staged steps.

---
*/