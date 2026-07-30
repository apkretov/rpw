#ifdef MINE // demo_textbook_4_18_sequential_blocks_ui

// Textbook 4.18 claim (baseline before async):
// Sequential login runs on the calling (UI) thread, so the UI is blocked
// for the full authenticate + request_info wait.
//
// It shows the textbook 4.18 baseline:
// A) Sequential login on the UI thread → UI blocked(~176 ms), ** 0 frames during login * *
// B) Same time budget with UI free → frames keep rendering(why the book moves to async)
// C) 40 sequential logins → wall time adds up on one thread; peak blocked = 1

#include <atomic>
#include <chrono>
#include <print>
#include <string>
#include <thread>
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
	note_blocked(+1); // UI/caller thread is occupied doing nothing useful
	std::this_thread::sleep_for(d);
	note_blocked(-1);
}

// Listing 4.18 shape: fully sequential on the calling thread.
static void process_login_4_18(std::string const& user) {
	blocking_backend_wait(80ms); // authenticate_user
	blocking_backend_wait(80ms); // request_current_info
	(void)user;                  // update_display
}

static int ui_pump(std::chrono::milliseconds budget) {
	auto end = Steady::now() + budget;
	int frames = 0;
	while (Steady::now() < end) {
		++frames;
		std::this_thread::sleep_for(16ms); // ~60 FPS tick
	}
	return frames;
}

int main() {
	print_file_line();

	std::println("=== Textbook point for Listing 4.18 ===");
	std::println("Sequential login blocks the UI/calling thread while waiting.\n");

	std::println("-- A) One sequential login ON the UI thread --");
	{
		peak_blocked = 0;
		auto start = Steady::now();
		process_login_4_18("alice");
		auto login_ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - start).count();
		std::println("login blocked UI for {} ms", login_ms);
		std::println("peak threads blocked waiting during login = {}", peak_blocked.load());
		std::println("UI frames during login = 0  (UI could not run until login returned)");
		auto frames_after = ui_pump(50ms);
		std::println("UI frames only AFTER login returned: {}\n", frames_after);
	}

	std::println("-- B) Contrast: if login were async, UI could pump during the wait --");
	{
		// Same total wait budget as one login (~160ms), but UI runs instead of blocking.
		auto frames = ui_pump(160ms);
		std::println("UI frames rendered in ~160ms when NOT blocked by sequential login: {}", frames);
		std::println("(Textbook moves to Listing 4.19 so the UI thread is not blocked.)\n");
	}

	std::println("-- C) Many sequential logins: wall time adds up on one thread --");
	{
		constexpr int N = 40;
		peak_blocked = 0;
		auto t0 = Steady::now();
		for (int i = 0; i < N; ++i)
			process_login_4_18("user" + std::to_string(i));
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(Steady::now() - t0).count();
		std::println("users = {}", N);
		std::println("wall time = {} ms  (roughly N * (auth + info))", ms);
		std::println("peak threads blocked waiting = {}", peak_blocked.load());
		std::println("Textbook: sequential is simple, but the UI/calling thread is stuck for every wait.");
	}
	return 0;
}

#endif