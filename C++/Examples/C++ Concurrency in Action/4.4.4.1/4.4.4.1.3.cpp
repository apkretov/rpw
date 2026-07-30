#ifdef MINE // demo_textbook_4_19_ui_free_but_blocked_workers

/*
Textbook 4.19 claim:
- async keeps the UI thread free
- but each background task still BLOCKS its worker thread while waiting

It shows the textbook 4.19 baseline:
A) Sequential on UI : login blocked UI ~166 ms
B) Async + UI pump : UI kept rendering frames while login ran
C) 40 logins : many workers blocked waiting at once
*/

#include <atomic>
#include <chrono>
#include <future>
#include <print>
#include <string>
#include <thread>
#include <vector>
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

static void blocking_backend_wait(std::chrono::milliseconds d) {
	note_blocked(+1); // this thread is occupied doing nothing useful
	std::this_thread::sleep_for(d);
	note_blocked(-1);
}

static void process_login_sequential(std::string const& user) {
	blocking_backend_wait(80ms); // authenticate
	blocking_backend_wait(80ms); // request info
	(void)user;
}

static std::future<void> process_login_4_19(std::string const& user) {
	return std::async(std::launch::async, [user] {
		blocking_backend_wait(80ms); // authenticate
		blocking_backend_wait(80ms); // request info
		(void)user;
	});
}

static void ui_pump(std::chrono::milliseconds budget) {
	auto end = Steady::now() + budget;
	int frames = 0;
	while (Steady::now() < end) {
		++frames;
		std::this_thread::sleep_for(16ms); // ~60 FPS tick
	}
	std::println("UI frames rendered: {}", frames);
}

int main() {
	print_file_line();
	std::println("=== Textbook point for Listing 4.19 ===");
	std::println("Goal: UI stays free, but worker threads still block while waiting.\n");

	std::println("-- A) Sequential login ON the UI thread --");
	{
		auto start = Steady::now();
		process_login_sequential("alice");
		auto login_ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - start).count();
		std::println("login blocked UI for {} ms", login_ms);
		ui_pump(50ms); // UI only runs after login returns
		std::println("");
	}

	std::println("-- B) Listing 4.19: login on background thread; UI keeps pumping --");
	{
		peak_blocked = 0;
		auto t0 = Steady::now();
		auto login = process_login_4_19("alice");
		ui_pump(200ms); // UI runs concurrently with login wait
		login.wait();
		std::println("login finished; peak blocked workers during this login: {}", peak_blocked.load());
		std::println("elapsed {} ms\n",
			std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count());
	}

	std::println("-- C) Many Listing 4.19 logins: many threads sit waiting --");
	{
		constexpr int N = 40;
		peak_blocked = 0;
		std::vector<std::future<void>> all;
		all.reserve(N);
		auto t0 = Steady::now();
		for (int i = 0; i < N; ++i)
			all.push_back(process_login_4_19("user" + std::to_string(i)));
		for (auto& f : all)
			f.wait();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count();
		std::println("users = {}", N);
		std::println("wall time = {} ms", ms);
		std::println("peak threads blocked waiting = {}  (textbook: large number doing nothing except waiting)",
			peak_blocked.load());
	}
	return 0;
}

#endif
