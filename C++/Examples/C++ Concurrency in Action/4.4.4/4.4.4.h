#pragma once

#pragma region MINE

#include <chrono>
#include <exception>
#include <future>
#include <print>
#include <string>
#include <thread>
#include "../experimental/future.h"

using user_id = long long;

struct user_data {
	user_id ui;
	std::string username;
	std::string pwd;
};

struct back_end {
	user_id authenticate_user(std::string const&, std::string const&) const {
		std::this_thread::sleep_for(std::chrono::milliseconds(2)); // short delay for 100-user teaching benchmark
		return 42;
	}

	user_data request_current_info(user_id id) const {
		std::this_thread::sleep_for(std::chrono::milliseconds(2)); // short delay for 100-user teaching benchmark
		return {id, "username", "pwd"};
	}

	// Teaching stand-ins for truly asynchronous backend IO (Listing 4.21).
	std::experimental::future<user_id> async_authenticate_user(std::string const& username, std::string const& password) const {
		return std::experimental::future<user_id>(std::async(
			std::launch::async, [=] { return authenticate_user(username, password); }));
	}

	std::experimental::future<user_data> async_request_current_info(user_id id) const {
		return std::experimental::future<user_data>(
			std::async(std::launch::async, [=] { return request_current_info(id); }));
	}
};

inline const back_end backend;

inline void update_display([[maybe_unused]] const user_data& info_to_display) {
#ifndef BENCHMARK_QUIET
	std::println("id = {}, user name = {}, password = {}", info_to_display.ui, info_to_display.username, info_to_display.pwd);
#endif
}

inline void display_error(std::exception const& e) { std::println("{}", e.what()); }
#pragma endregion // MINE
