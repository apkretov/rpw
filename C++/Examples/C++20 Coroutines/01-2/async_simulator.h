#pragma once

#pragma region MINE

#include <algorithm>
#include <chrono>
#include <ostream>
#include <print>
#include <thread>
#include <utility>

using namespace std::chrono_literals;

template<typename Work> // Starts work on another thread and returns immediately. sleep_for stands in for network/database I/O that does not occupy the caller.
void simulate_async(const char* name, Work work) {
	std::println("{} 333 {}: launching from thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
	std::jthread([name, work_ = std::move(work)] {
		std::println("{} 444/555 {}: running on thread {}", std::this_thread::get_id(), name, std::this_thread::get_id());
		const auto start = std::chrono::steady_clock::now();
		std::this_thread::sleep_for(500ms);
		const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
		std::println("{} 888 {}: finished in {} ms on thread {}", std::this_thread::get_id(), name, ms, std::this_thread::get_id());
		work_();
	}).detach();
}

#pragma endregion //MINE
