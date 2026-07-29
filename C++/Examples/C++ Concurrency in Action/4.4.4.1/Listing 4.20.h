#pragma once

#include <exception>
#include <string>
#include "../experimental/future.h"
#include "../4.4.3/Listing 4.17.h" // spawn_async
#include "4.4.4.1.h"

std::experimental::future<void> process_login(std::string const& username, std::string const& password) { // A function to process user login with continuations
	return spawn_async([=]() {
		return backend.authenticate_user(username, password);
	}).then([](std::experimental::future<user_id> id) {
		return backend.request_current_info(id.get());
	}).then([](std::experimental::future<user_data> info_to_display) {
		try {
			update_display(info_to_display.get());
		}
		catch (std::exception& e) {
			display_error(e);
		}
});
}