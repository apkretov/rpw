#pragma once

#include <exception>
#include <string>
#include "4.4.4.h"

void process_login(std::string const& username, std::string const& password) { // A simple sequential function to process user login
	try {
		user_id const id = backend.authenticate_user(username, password);
		user_data const info_to_display = backend.request_current_info(id);
		update_display(info_to_display);
	}
	catch (std::exception& e) {
		display_error(e);
	}
}