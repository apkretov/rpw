#include "connection.h"
#include "database.h"
#include <format>
#include "parsed_request.h"
#include "../../stdafx.h"

#include <future>
#include <print>
#include <thread>

Database database;

void handle_request(connection& conn, std::promise<void>& done) {
	LogDuration ld(std::format("{} 222 handle_request", std::this_thread::get_id())); //MINE
	conn.async_read([&conn, &done](std::string request) {
		auto parsed = parse_request(request);
		database.async_query(parsed.id, [&conn, &done](auto data) {
			auto response = compute_response(data);
			conn.async_write(response, [&done]() {
				done.set_value();
			});
		});
	});
}

#pragma region MINE
int main() {
	print_file_line();
	
	std::println("{} 111 main thread = {}", std::this_thread::get_id(), std::this_thread::get_id());

	connection conn;
	std::promise<void> done;
	auto future = done.get_future();

	handle_request(conn, done);
	std::println("{} 555/444 handle_request returned immediately", std::this_thread::get_id());

	LogDuration ld(std::format("{} 666 main waiting for async request", std::this_thread::get_id()));
	while (future.wait_for(200ms) != std::future_status::ready)
		std::println("{} 777   [main] waiting for ~200ms...", std::this_thread::get_id());

	return 0;
}
#pragma endregion //MINE

/*
# Execution order explanation
_Exported on 8/24/2026 at 18:42:26 GMT+3 from Cursor (3.17.8)_

---

**User**

Here’s the project output. I added thread IDs and sequence numbers to std::println so that we can follow the execution order. Now, explain everything step by step.

The output:

File: C:\_\rpw\C++\Examples\C++20 Coroutines\01-2\01-2.cpp      Line: 28

36476 111 main thread = 36476
36476 222 handle_request: started...
36476 333 async_read: launching from thread 36476
36476 222 handle_request: execution time = 5 milliseconds
12444 444/555 async_read: running on thread 12444
36476 555/444 handle_request returned immediately
36476 666 main waiting for async request: started...
36476 777   [main] waiting for ~200ms...
36476 777   [main] waiting for ~200ms...
12444 888 async_read: finished in 512 ms on thread 12444
12444 333 async_query: launching from thread 12444
19860 444/555 async_query: running on thread 19860
36476 777   [main] waiting for ~200ms...
36476 777   [main] waiting for ~200ms...
19860 888 async_query: finished in 500 ms on thread 19860
19860 333 async_write: launching from thread 19860
29932 444/555 async_write: running on thread 29932
36476 777   [main] waiting for ~200ms...
36476 777   [main] waiting for ~200ms...
36476 777   [main] waiting for ~200ms...
29932 888 async_write: finished in 515 ms on thread 29932
19860 999 200 OK item-42
36476 666 main waiting for async request: execution time = 1551 milliseconds

---

**Cursor**

I'll read the source and walk through the logged sequence against the coroutine flow.

This example is **callback-style async**, not coroutines yet — nested lambdas, each kicked off by `simulate_async` on a detached `jthread` that sleeps ~500ms.

Thread legend from your run:
| ID | Role |
|----|------|
| **36476** | main |
| **12444** | `async_read` worker |
| **19860** | `async_query` worker |
| **29932** | `async_write` worker |

---

### 1. Startup (main)

```
36476 111 main thread = 36476
```

`main` creates `connection`, a `promise`/`future` pair, then calls `handle_request`.

---

### 2. `handle_request` starts and launches read

```
36476 222 handle_request: started...
36476 333 async_read: launching from thread 36476
36476 222 handle_request: execution time = 5 milliseconds
```

On the main thread:
1. `LogDuration` starts.
2. `conn.async_read(...)` → `simulate_async` prints **333**, spawns a worker, **returns immediately**.
3. `handle_request` returns (~5 ms). The nested callbacks are **not** run yet — only scheduled.

Nothing blocks waiting for I/O inside `handle_request`.

---

### 3. Race: worker vs main

```
12444 444/555 async_read: running on thread 12444
36476 555/444 handle_request returned immediately
```

After launch, two threads run in parallel:
- Worker **12444** prints “running” and starts its 500 ms sleep.
- Main prints “returned immediately”.

`444/555` vs `555/444` is intentional: either line can win; order is not guaranteed.

---

### 4. Main polls while I/O runs

```
36476 666 main waiting for async request: started...
36476 777   [main] waiting for ~200ms...
36476 777   [main] waiting for ~200ms...
```

Main loops `future.wait_for(200ms)` until `done.set_value()`. Promise is still unset, so it keeps printing **777**.

---

### 5. Read finishes → query starts (thread 12444)

```
12444 888 async_read: finished in 512 ms on thread 12444
12444 333 async_query: launching from thread 12444
19860 444/555 async_query: running on thread 19860
```

Worker finishes sleep, then runs the read callback (still on **12444**):

```15:23:c:\_\rpw\C++\Examples\C++20 Coroutines\01-2\01-2.cpp
	conn.async_read([&conn, &done](std::string request) {
		auto parsed = parse_request(request);
		database.async_query(parsed.id, [&conn, &done](auto data) {
			auto response = compute_response(data);
			conn.async_write(response, [&done]() {
				done.set_value();
			});
		});
	});
```

- Callback gets `"42"` → `parse_request` → `id = 42`.
- `async_query` launches from **12444** (**333**), new worker **19860** starts sleeping.

Main keeps printing **777** in parallel.

---

### 6. Query finishes → write starts (thread 19860)

```
19860 888 async_query: finished in 500 ms on thread 19860
19860 333 async_write: launching from thread 19860
29932 444/555 async_write: running on thread 29932
```

On **19860**:
- Query callback runs with `"item-42"`.
- `compute_response` builds the response string.
- `async_write` launches; worker **29932** sleeps ~500 ms.

Again, main is still polling (**777**).

---

### 7. Write finishes → promise signaled

```
29932 888 async_write: finished in 515 ms on thread 29932
19860 999 200 OK item-42
36476 666 main waiting for async request: execution time = 1551 milliseconds
```

On write worker **29932**, after sleep:
1. Print response (`999` — note: that `println` runs inside the write lambda, so the thread ID shown is whoever runs that lambda body; your log shows **19860**, which can happen if timing/capture differs, but the important part is the response text).
2. Inner callback: `done.set_value()`.

Main’s next `wait_for` sees ready → loop exits → `LogDuration` prints **~1551 ms** ≈ three × ~500 ms I/O stages.

---

### Mental model

```
main ──► handle_request ──► async_read (detach) ──► return immediately
				│
				│  (~500ms later, worker A)
				▼
		   parse + async_query (detach)
				│
				│  (~500ms later, worker B)
				▼
		   compute + async_write (detach)
				│
				│  (~500ms later, worker C)
				▼
		   print "200 OK…" + done.set_value()
				│
				▼
		   main’s future becomes ready
```

**Takeaways:**
1. `handle_request` returns in milliseconds; real work happens on other threads.
2. Continuations nest: read → query → write → `set_value`.
3. Each `simulate_async` is “fire and forget”: launch thread, sleep, then run the callback.
4. Main’s **777** lines are just polling while those three stages run in series (~1.5 s total).
5. Thread IDs change at each stage because each op gets its own detached worker.

This nested-callback shape is exactly the “callback hell” that C++20 coroutines in later examples are meant to flatten into linear-looking `co_await` code.
*/