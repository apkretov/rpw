#pragma once

#pragma region MINE

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 // Windows 10; Boost.Asio requires this on MSVC
#endif

#include <boost/asio.hpp>
#include <atomic>
#include <exception>
#include <print>
#include <string>
#include <thread>
#include "4.4.4.1.5.h"

using user_id = long long;

struct user_data {
	user_id ui;
	std::string username;
	std::string pwd;
};

inline std::atomic<bool> quiet_display{false};

inline boost::asio::awaitable<void> simulated_io() { // Asio timer: the wait lives in the reactor, not on a sleeping thread.
	boost::asio::steady_timer timer(co_await boost::asio::this_coro::executor);
	timer.expires_after(simulated_io_latency);
	in_flight_guard g;
	co_await timer.async_wait(boost::asio::use_awaitable);
}

struct back_end {
	user_id authenticate_user(std::string const&, std::string const&) const {
		note_blocked(+1);
		std::this_thread::sleep_for(simulated_io_latency);
		note_blocked(-1);
		return 42;
	}

	user_data request_current_info(user_id id) const {
		note_blocked(+1);
		std::this_thread::sleep_for(simulated_io_latency);
		note_blocked(-1);
		return {id, "username", "pwd"};
	}

	// Listing 4.21 async backend: same 80 ms "network/DB" wait, but as an Asio timer.
	boost::asio::awaitable<user_id> async_authenticate_user(std::string, std::string) const {
		co_await simulated_io();
		co_return 42;
	}

	boost::asio::awaitable<user_data> async_request_current_info(user_id id) const {
		co_await simulated_io();
		co_return user_data{id, "username", "pwd"};
	}
};

inline const back_end backend;

inline void update_display([[maybe_unused]] const user_data& info_to_display) {
	if (quiet_display.load())
		return;
	std::println("id = {}, user name = {}, password = {}", info_to_display.ui, info_to_display.username, info_to_display.pwd);
}

inline void display_error(std::exception const& e) { std::println("{}", e.what()); }
#pragma endregion // MINE
