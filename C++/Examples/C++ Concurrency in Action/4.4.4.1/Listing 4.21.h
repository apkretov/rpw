#pragma once

#include <exception>
#include <string>
#include "../experimental/future.h"
#include "4.4.4.1.h"

#ifndef AUTO
std::experimental::future<void> process_login(std::string const& username, std::string const& password) { // A function to process user login with fully asynchronous operations
	return backend.async_authenticate_user(username, password).then(
		[](std::experimental::future<user_id> id) {
			return backend.async_request_current_info(id.get());
		}).then([](std::experimental::future<user_data> info_to_display) {
			try {
				update_display(info_to_display.get());
			}
			catch (std::exception& e) {
				display_error(e);
			}
		});
}

#else //AUTO
std::experimental::future<void> process_login(std::string const& username, std::string const& password) { // A function to process user login with fully asynchronous operations
	return backend.async_authenticate_user(username, password).then(
		[](auto id) { // With C++14 generic lambdas, the types of the futures in the lambda parameters can be replaced with auto, which simplifies the code.
			return backend.async_request_current_info(id.get());
		}).then([](std::experimental::future<user_data> info_to_display) {
			try {
				update_display(info_to_display.get());
			}
			catch (std::exception& e) {
				display_error(e);
			}
		});
}
#endif //AUTO