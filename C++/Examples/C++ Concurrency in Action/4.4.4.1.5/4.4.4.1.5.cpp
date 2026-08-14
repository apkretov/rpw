#pragma region MINE 
// demo_textbook_4_21_asio_coroutines - See the note about the Non-Concurrency-TS Asio + co_await substitute below.

/*
Textbook 4.21 claim:
Backend operations become ready WITHOUT blocking a worker thread while waiting for network/DB.
Continuations keep the chain async.

It shows the textbook 4.21 baseline::
A) UI still free during login (io_context runs on a background thread)
B) Blocking backend: high peak blocked threads
C) Non-blocking Asio backend: peak threads blocked waiting = 0 (timers sit in the reactor)
*/

#include <chrono>
#include <format>
#include <future>
#include <print>
#include <string>
#include <thread>
#include <vector>
#include "../../stdafx.h"
#include "4.4.4.1.5.h"
#include "Listing 4.21.h"

static std::future<void> process_login_blocking(std::string username, std::string password) { // Listing 4.20-like: a dedicated thread sleeps through both IO waits.
	return std::async(std::launch::async, [username = std::move(username), password = std::move(password)] {
		user_id id = backend.authenticate_user(username, password);
		user_data info = backend.request_current_info(id);
		(void)info;
	});
}

static std::future<void> spawn_login(boost::asio::io_context& io, std::string username, std::string password) {
	return boost::asio::co_spawn(io, process_login(std::move(username), std::move(password)), boost::asio::use_future);
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

template<typename Launch, typename... Notes>
static void run_many_logins(Launch launch, Notes&&... notes) {
	constexpr int N = 40;
	peak_blocked = 0;
	peak_in_flight = 0;

	std::vector<std::future<void>> all;
	all.reserve(N);
	auto t0 = Steady::now();
	for (int i = 0; i < N; ++i)
		all.emplace_back(launch(i));
	for (const auto& f : all)
		f.wait();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count();
	std::println("users = {}", N);
	std::println("wall time = {} ms", ms);
	std::println("peak threads blocked waiting = {}", peak_blocked.load());
	std::println("peak in-flight async waits = {}", peak_in_flight.load());
	(std::println("{}", notes), ...);
}

int main() {
	print_file_line();

	std::println("=== Textbook point for Listing 4.21 (Asio + co_await) ===");
	std::println("Async backend waits complete without one blocked thread per wait.\n");

	boost::asio::io_context io;
	auto work = boost::asio::make_work_guard(io);
	std::jthread io_thread([&io] { io.run(); });

	std::println("-- A) UI stays free while 4.21-style login runs --");
	{
		auto login = spawn_login(io, "alice", "secret");
		ui_pump(50ms);
		{
			LogDuration ld("login.wait after ui_pump(50ms): adjust it vs. ORIG ui_pump(200ms) to measure the effect");
			login.wait();
		}
		std::println("login finished\n");
	}

	std::println("-- B) Many logins with BLOCKING backend --");
	run_many_logins(
		[](int i) { return process_login_blocking(std::format("user {}", i), "secret"); },
		"(many workers stuck in sleep/wait)\n"
	);

	std::println("-- C) Many logins with NON-BLOCKING Asio backend (Listing 4.21 idea) --");
	quiet_display = true;
	run_many_logins(
		[&io](int i) { return spawn_login(io, std::format("user {}", i), "secret"); },
		"Textbook: waits are multiplexed; peak blocked stays at 0 (reactor, not sleep).",
		"co_await is the continuation; Asio unwraps the next awaitable (no future<future<T>>)."
	);

	work.reset();
	return 0;
}
#pragma endregion //MINE

/*
The note about the Non-Concurrency-TS Asio + co_await substitute

Listing 4.21 is now **Asio + `co_await`**, using Boost at `c:\boost_1_84_0\`. The experimental `.then` chain is gone.

The login function is the textbook pipeline written as a coroutine. Each `co_await` is the continuation:

```11:20:c:\_\rpw\C++\Examples\C++ Concurrency in Action\4.4.4.4\Listing 4.21.h
inline boost::asio::awaitable<void> process_login(std::string username, std::string password) { // Parameters by value: coroutine frames outlive the call expression.
	try {
		user_id id = co_await backend.async_authenticate_user(std::move(username), std::move(password));
		user_data info_to_display = co_await backend.async_request_current_info(id);
		update_display(info_to_display);
	}
	catch (std::exception& e) {
		display_error(e);
	}
}
```

The 80 ms “network/DB” wait is a `steady_timer` on `this_coro::executor`, not a sleeping worker. `main` runs `io_context` on a background thread so the UI pump stays free, same as the original A/B/C demo.

A Debug|x64 run:

| | Wall | Peak blocked threads | Peak in-flight waits |
|---|---|---|---|
| **B** blocking `std::async` | 1137 ms | 10 | 0 |
| **C** Asio + `co_await` | 190 ms | **0** | **40** |

C is ~2×80 ms because every login’s auth and info timers overlap on the reactor. That is the Listing 4.21 point: waits are multiplexed, and no thread is parked per user.

`process_login` takes strings **by value** so the coroutine frame does not dangle after `co_spawn(io, process_login("alice", "secret"), …)`. That is the one intentional deviation from the textbook’s `const&`.


## Practical takeaway for your use case

Given your focus on C++ concurrency and low‑latency systems :

-Use `boost: : asio::io_context` (or `asio::io_context`) as the * *core async runtime * *.
- Use:
-Handlers or coroutines for internal logic.
- `use_future` only when you need to interface with code that expects `std::future`.
- Treat `std::experimental::future::then` as an interesting conceptual ancestor, but not as a primary tool for performance‑critical paths.
*/
