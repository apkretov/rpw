#ifdef MINE // demo_textbook_4_20_continuations_still_block

/*
Textbook 4.20 claim:
Continuations split the login into chained stages.
BUT if backend calls still block, worker threads are STILL blocked while waiting.
 
It shows the textbook 4.20 baseline:
- Continuations completed all auth / info stages
- Still `peak threads blocked waiting = 40` — chaining ≠ non - blocking IO
*/

#include <atomic>
#include <chrono>
#include <future>
#include <print>
#include <string>
#include <thread>
#include <vector>
#include "../4.4.3/Listing 4.17.h"
#include "../experimental/future.h"
#include "../../stdafx.h"

using namespace std::chrono_literals;
using Steady = std::chrono::steady_clock;

static std::atomic<int> blocked_waiting{0};
static std::atomic<int> peak_blocked{0};
static std::atomic<int> stage_auth_done{0};
static std::atomic<int> stage_info_done{0};

static void note_blocked(int delta) {
	int cur = blocked_waiting.fetch_add(delta) + delta;
	int peak = peak_blocked.load();
	while (cur > peak && !peak_blocked.compare_exchange_weak(peak, cur)) {
	}
}

static long authenticate_blocking(std::string const&) {
	note_blocked(+1);
	std::this_thread::sleep_for(80ms); // blocking network/DB wait
	note_blocked(-1);
	stage_auth_done.fetch_add(1);
	return 42;
}

static int request_info_blocking(long) {
	note_blocked(+1);
	std::this_thread::sleep_for(80ms); // blocking network/DB wait
	note_blocked(-1);
	stage_info_done.fetch_add(1);
	return 1;
}

// Listing 4.20 shape: spawn_async + .then chain, with BLOCKING backend calls.
static std::experimental::future<void> process_login_4_20(std::string user) {
	return spawn_async([user] {
		return authenticate_blocking(user);
	}).then([](std::experimental::future<long> id) {
		return request_info_blocking(id.get());
	}).then([](std::experimental::future<int> info) {
		info.get(); // must wait; otherwise the chain future becomes ready too early
	});
}

// Listing 4.19 shape for comparison: one async task holding a thread for BOTH waits.
static std::future<void> process_login_4_19(std::string user) {
	return std::async(std::launch::async, [user] {
		authenticate_blocking(user);
		request_info_blocking(42);
	});
}

int main() {
	print_file_line();
	std::println("=== Textbook point for Listing 4.20 ===");
	std::println("Continuations chain stages; blocking backend still occupies threads.\n");

	constexpr int N = 40;

	std::println("-- A) Listing 4.20 continuations (blocking backend) --");
	{
		peak_blocked = 0;
		stage_auth_done = 0;
		stage_info_done = 0;
		std::vector<std::experimental::future<void>> all;
		all.reserve(N);
		auto t0 = Steady::now();
		for (int i = 0; i < N; ++i)
			all.push_back(process_login_4_20("user" + std::to_string(i)));
		for (auto& f : all)
			f.wait();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count();
		std::println("users = {}", N);
		std::println("wall time = {} ms", ms);
		std::println("auth stages completed = {}", stage_auth_done.load());
		std::println("info stages completed = {}", stage_info_done.load());
		std::println("peak threads blocked waiting = {}", peak_blocked.load());
		std::println("(split into continuations, but waits still block threads)\n");
	}

	std::println("-- B) Listing 4.19 single async task (same blocking backend) --");
	{
		peak_blocked = 0;
		stage_auth_done = 0;
		stage_info_done = 0;
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
		std::println("peak threads blocked waiting = {}", peak_blocked.load());
		std::println("Textbook: 4.20 chains stages, but does NOT remove blocked waits yet.");
	}
	return 0;
}

#endif