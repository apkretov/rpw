#pragma once

#pragma region MINE

#include <exception>
#include <string>
#include "4.4.4.1.h"

/*
Listing 4.21 as Asio + coroutines.
Textbook: async_authenticate_user().then([](future id){ return async_request_current_info(id.get()); }).then(...)
Here: code after each co_await *is* the continuation; no future-unwrapping, no .then.
*/

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
#pragma endregion //MINE
