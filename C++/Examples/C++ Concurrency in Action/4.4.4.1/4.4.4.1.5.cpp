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
#include <condition_variable>
#include <future>
#include <mutex>
#include <print>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include "../experimental/future.h"
#include "../../stdafx.h"

using namespace std::chrono_literals;
using Steady = std::chrono::steady_clock;

static std::atomic<int> blocked_waiting{0};
static std::atomic<int> peak_blocked{0};

static void note_blocked(int delta) {
	int cur = blocked_waiting.fetch_add(delta) + delta;
	int peak = peak_blocked.load();
	while (cur > peak && !peak_blocked.compare_exchange_weak(peak, cur)) {
	}
}

struct IoEvent {
	Steady::time_point when;
	std::experimental::promise<long> prom;
	long value;
};

class NonBlockingBackend { // Tiny completion service: ONE thread waits; many requests stay non-blocking for callers.
public:
	NonBlockingBackend() : stop(false), thr([this] { run(); }) {}
	
	~NonBlockingBackend() {
		{
			std::scoped_lock lk(mx);
			stop = true;
		}
		cv.notify_all();
		thr.join();
	}

	std::experimental::future<long> async_authenticate(std::string const&) { // Returns immediately; no per-request worker thread sleeps for the IO wait.
		std::experimental::promise<long> p;
		auto fut = p.get_future();
		{
			std::scoped_lock lk(mx);
			q.emplace(Steady::now() + 80ms, std::move(p), 42);
		}
		cv.notify_one();
		return fut;
	}

	std::experimental::future<long> async_request_info(long id) {
		std::experimental::promise<long> p;
		auto fut = p.get_future();
		{
			std::scoped_lock lk(mx);
			q.emplace(Steady::now() + 80ms, std::move(p), id);
		}
		cv.notify_one();
		return fut;
	}

private:
	void run() {
		for (;;) {
			std::unique_lock lk(mx);
			cv.wait(lk, [&] { return stop || !q.empty(); });
			if (stop && q.empty())
				return;

			auto ev = std::move(q.front());
			q.pop();
			auto when = ev.when;
			lk.unlock();

			note_blocked(+1); // Only this single IO thread blocks for the wait — not one thread per request.
			std::this_thread::sleep_until(when);
			note_blocked(-1);
			ev.prom.set_value(ev.value);
		}
	}

	std::mutex mx;
	std::condition_variable cv;
	std::queue<IoEvent> q;
	bool stop;
	std::jthread thr;
};

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

static std::experimental::future<void> process_login_4_21(NonBlockingBackend& backend, std::string user) { // Listing 4.21-like: async backend + future-unwrapping.
	return backend.async_authenticate(user)
		.then([&backend](std::experimental::future<long> id) {
			return backend.async_request_info(id.get()); // returns future<long> — Continuations TS unwraps to future<long>
		})
		.then([](std::experimental::future<long> info) {
			info.get(); // update_display; must wait for unwrapped future
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
	NonBlockingBackend backend;

	std::println("-- A) UI stays free while 4.21-style login runs --");
	{
		auto login = process_login_4_21(backend, "alice");
		ui_pump(200ms);
		login.wait();
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