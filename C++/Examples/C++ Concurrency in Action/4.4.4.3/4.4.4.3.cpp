#ifndef MINE
/*
Simple TCP client: connect and read
This example connects to a server, reads a line, and closes. It shows how sockets are tied to io_context.

Key ideas:
tcp::resolver, tcp::socket are constructed with io.
All async operations (async_connect, async_write, async_read_some) post their completion handlers to io.
io.run() drives everything: when the OS says “connected”, “written”, “data ready”, Asio calls your lambdas.
You don’t manually “wait” anywhere; the event loop does it.

Why io_context and not just threads?

Without io_context, a naive server might do:
One thread per connection, each blocking on recv()/send().
Many threads → more context switches, more memory, harder to scale.

With io_context:
One (or a few) threads run io.run().
Thousands of connections are handled via callbacks when the OS says they’re ready.
You write code as “start async op + callback”, and io_context handles scheduling.

This is especially useful in low-latency systems (e.g., trading gateways): you can have a small, fixed thread pool and still handle many network streams efficiently.

See the note about Boost.Asio + io_context vs. std::experimental::future::then() below.
*/

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <array>
#include "../../stdafx.h"

static void start_read(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io) {
	auto buf = std::make_shared<std::array<char, 1024>>(); // Async read some bytes
	socket.async_read_some(boost::asio::buffer(*buf), [&, buf](const boost::system::error_code& ec, std::size_t n) {
		if (ec) {
			std::cerr << "Read error: " << ec.message() << "\n";
			io.stop();
			return;
		}

		std::cout << "Received " << n << " bytes:\n\n";
		std::cout.write(buf->data(), static_cast<std::streamsize>(n)); // Application payload from the peer (here: HTTP response text), not socket/Asio internals
		std::cout << "\n";
		io.stop();  // we’re done
	});
}

static void start_http_exchange(boost::asio::ip::tcp::socket& socket, boost::asio::io_context& io, const std::string& host) {
	auto request = std::make_shared<std::string>( // No space after \r\n — header lines must start with the field name (RFC 7230). Host must match the server you connected to.
		"GET / HTTP/1.1\r\n"
		"Host: " + host + "\r\n"
		"Connection: close\r\n"
		"\r\n"); // Keep the request alive until async_write finishes (buffer() only views the data; it does not copy it).
	boost::asio::async_write(socket, boost::asio::buffer(*request), [&, request](const boost::system::error_code& ec, std::size_t) {
		if (ec) {
			std::cerr << "Write error: " << ec.message() << "\n";
			io.stop();
			return;
		}
		start_read(socket, io);
	});
}

int main() {
	print_file_line();

	try {
		const std::string host = "google.com"; // Try "example.com" too; Host header stays in sync via start_http_exchange(..., host)
		boost::asio::io_context io;
		boost::asio::ip::tcp::resolver resolver(io); // Resolve host (e.g. example.com:80)
		auto endpoints = resolver.resolve(host, "80");
		boost::asio::ip::tcp::socket socket(io);

		boost::asio::async_connect(socket, endpoints, [&](const boost::system::error_code& ec, const boost::asio::ip::tcp::endpoint&) { // Async connect
			if (ec) {
				std::cerr << "Connect error: " << ec.message() << "\n";
				io.stop();  // stop the event loop
				return;
			}
			std::cout << "Connected\n\n";
			start_http_exchange(socket, io, host);
		});

		io.run(); // Run the event loop
		std::cout << "Finished\n";
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
#endif // MINE

/*
The note about Boost.Asio + io_context vs. std::experimental::future::then()

---

```
# <q>
All async operations (async_connect, async_write, async_read_some) post their completion handlers to io.
io.run() drives everything: when the OS says “connected”, “written”, “data ready”, Asio calls your lambdas.
You don’t manually “wait” anywhere; the event loop does it.
</q>

This seems very similar to continuation style std::experimental::future::then from the Concurrency TS. What are the similarities, differences, advantages, and disadvantages of the two techniques, assuming they are indeed related, as I understand them to be?
```

You’re right to see a strong similarity: both `boost::asio::io_context` + callbacks and `std::experimental::future::then` are ways to express **“do this now, and when it’s done, continue with that”** without blocking the calling thread. But they live in different async models and have different trade‑offs.

Below is a focused comparison from a C++ systems / low‑latency perspective.

***

## Core mental models

### Boost.Asio + `io_context`

- Model: **event loop + completion handlers**.
- You start an async op:

```cpp
socket.async_read_some(buffer,
	[](const boost::system::error_code& ec, std::size_t n) {
		// continuation
	});
```

- The handler is posted to an `io_context` executor and runs when the OS signals completion.[^3_1][^3_2][^3_3]
- The “scheduler” is explicit: an `io_context` (or other executor) that you run with `io.run()`.[^3_4][^3_5][^3_1]


### `std::future` + `.then()` (Concurrency TS)

- Model: **future + continuation**.
- You have a `std::experimental::future<T>` representing a value that will be ready later.
- You attach a continuation:

```cpp
std::experimental::future<int> f = start_async();
f.then([](std::experimental::future<int> g) {
	int x = g.get();  // guaranteed ready
	// continuation
});
```

- The continuation runs on some executor / thread when the future becomes ready (details depend on implementation / executor policy).[^3_6]

Both are “non‑blocking continuation” styles, but they differ in **who controls execution**, **how composition works**, and **cost model**.

***

## Similarities

- Both avoid blocking the caller while waiting for I/O or other async work.[^3_2][^3_3]
- Both express control flow as a chain of callbacks / continuations.
- Both can be used to build higher‑level abstractions (e.g., pipelines, request/response flows).

***

## Key differences

### 1. Execution context and scheduling

**Asio:**

- Explicit `io_context` (or other executor) that you create and run.[^3_5][^3_1]
- You decide:
	- How many threads run `io.run()`.
	- Which `io_context` / executor each operation uses.
- Handlers run on threads that are inside `io_context::run()` (or equivalent).[^3_1][^3_4]

**`future::then`:**

- No explicit event loop in the basic model.
- Where the continuation runs depends on:
	- The future’s associated executor (if any).
	- Library / runtime policy.
- In many simple examples, there’s an implicit thread pool or the thread that sets the value.

For systems code (trading gateways, servers), Asio’s explicit control over threads and executors is usually preferable.

***

### 2. Composition and chaining

**Asio:**

- Historically, you compose via nested callbacks or helper functions.
- Modern Asio supports:
	- Coroutines (`co_await` on `awaitable`).
	- `use_future` to get `std::future` from async ops.[^3_7][^3_8][^3_9]
- But the core model is still “initiate async op + completion handler”.

**`future::then`:**

- Designed for chaining:

```cpp
f.then(g).then(h);
```

- Each `.then()` returns a new future, making linear pipelines natural.
- However, the Concurrency TS version is known to be heavy and awkward in practice (see below).[^3_6]

If you like monadic chaining, `future::then` feels more “functional”; Asio feels more “event‑driven”.

***

### 3. Error handling

**Asio:**

- Errors are passed explicitly to handlers (usually as `boost::system::error_code` or exception).[^3_3]
- Pattern:

```cpp
[](const boost::system::error_code& ec, auto result) {
	if (ec) { handle error... } else { use result... }
};
```

- Very explicit, easy to integrate with low‑level error codes.

** `future::then`:**

-Errors are represented as broken futures / exceptions stored in the future.
- Continuation must call `.get()` and handle exceptions, or inspect future state.
- Can be less explicit in low‑level code where you already use error codes.

* **

### 4. Cost and performance

This is crucial for low‑latency C++.

* *Asio:**

-Completion handlers are typically :
-Type‑erased only if you choose to(e.g., via `std::function`), but often they’re just templates with no extra allocation.
- Executed directly on an `io_context` thread with minimal overhead.
- No mandatory heap allocation per async op beyond what the operation itself needs.[^ 3_2][^ 3_3]
- Widely used in performance‑sensitive networking code.

* *`std::experimental::future::then`: * *

-Known issues(as described by people familiar with the proposal and implementations) :[^ 3_6]
- `future`/`promise` usually allocate shared state.
- `.then()` often involves :
-Type erasure(`std::function`‑like).
- Reference counting.
- Locks / condition variables to avoid races between `set_value` and `then`.
- Result: multiple allocations, indirection, and synchronization per continuation.
- In practice, this is considered * *too heavy * *for high‑frequency / low‑latency paths.[^ 3_6]

For anything performance‑critical(e.g., trading), Asio’s model is usually far more suitable.

***

### 5. Integration with I / O

* *Asio:**

-Built specifically for I / O : sockets, timers, serial ports, etc.[^ 3_10][^ 3_5][^ 3_1]
- Async ops are first‑class and tightly integrated with `io_context`.
- Completion tokens let the same async op be used with :
-Callbacks
- `std: : future`
- Coroutines(`co_await`)[^ 3_8][^ 3_9]

* *`future::then`: * *

-Generic “will be ready someday” abstraction, not tied to I / O.
- To use with sockets, you need a library that :
-Performs async I / O internally.
- Exposes results as futures.
- The standard library itself doesn’t define async network ops; you rely on third‑party libs or custom wrappers.[^ 3_10]

So for network / timer / signal work, Asio is the natural fit.

***

### 6. Lifetime and ownership

* *Asio:**

-Objects(sockets, timers) are tied to an `io_context`.
- Common pattern :
-Keep the I / O object alive until the operation completes.
- Use `shared_from_this` in handlers to manage lifetimes safely.
- You have explicit control over when handlers can no longer fire(e.g., by closing the socket, stopping `io_context`).[^ 3_4][^ 3_1]

* *`future::then`: * *

-The future’s shared state keeps things alive until all continuations and the future itself are gone.
- Easier to accidentally extend lifetimes or create hidden dependencies in complex chains.
- Less obvious control over exactly when and where continuations run.

* **

## Advantages and disadvantages

### Boost.Asio + `io_context`

* *Advantages:**

-Explicit, fine‑grained control over threads and scheduling.[^ 3_5][^ 3_1]
- Low overhead, suitable for high‑performance / low‑latency systems.[^ 3_3][^ 3_2]
- Mature, widely used for networking and I / O.[^ 3_10]
- Supports multiple styles : callbacks, futures, coroutines.[^ 3_9][^ 3_7][^ 3_8]

* *Disadvantages : **

-More “plumbing” if you want pure functional chaining.
- You must manage `io_context` and executors explicitly.
- Callback nesting can get ugly without coroutines or helpers.


### `std::experimental::future::then`

* *Advantages:**

-Natural for chaining computations : `f.then(g).then(h)`.
- Abstracts away the executor in simple cases.
- Good conceptual fit for CPU‑bound async pipelines.

** Disadvantages:**

-Heavyweight : allocations, type erasure, locking, reference counting.[^ 3_6]
- Concurrency TS is not widely adopted in production; many consider it flawed.[^ 3_6]
- Less control over where and when continuations run.
- Not integrated with I / O; you need extra layers to use it for sockets / timers.[^ 3_10]

In practice, for systems / trading / servers, Asio’s model is usually the better foundation; futures are more often used as a* bridge* to other code, not as the core async engine.

***

## How they relate in modern C++

Modern Asio actually unifies these ideas :

-Every async op can take a * *completion token * *:
	-Plain callback → classic handler.
	- `boost: : asio::use_future` → returns `std::future`.[^ 3_7][^ 3_8][^ 3_9]
	- Coroutine → `co_await` on `awaitable`.

	So you can think of Asio as the * *execution engine**, and `std::future` / coroutines as * *views * *on top of it.

	Example:

```cpp
boost::asio::awaitable<int> do_work() {
	int x = co_await socket.async_read_some(buffer, boost::asio::use_awaitable);
	// more async ops...
	co_return x;
}

// Or:
std::future<int> f =
boost::asio::co_spawn(io, do_work(), boost::asio::use_future);
```

Here, the underlying scheduling is still `io_context`; the future is just a convenience wrapper.[^ 3_8][^ 3_9][^ 3_7]

* **

## Practical takeaway for your use case

Given your focus on C++ concurrency and low‑latency systems :

-Use `boost: : asio::io_context` (or `asio::io_context`) as the * *core async runtime * *.
- Use:
-Handlers or coroutines for internal logic.
- `use_future` only when you need to interface with code that expects `std::future`.
- Treat `std::experimental::future::then` as an interesting conceptual ancestor, but not as a primary tool for performance‑critical paths.
*/