#pragma once

#pragma region MINE

#include "simulated_duration.h"
#include <print>
#include <string>
#include <thread>

struct connection {
	std::string read() const {
		std::this_thread::sleep_for(simulated_duration);
		return "42";
	}

	void write(const std::string& response) const {
		std::this_thread::sleep_for(simulated_duration);
		std::println("{}", response);
	}
};
#pragma endregion //MINE
