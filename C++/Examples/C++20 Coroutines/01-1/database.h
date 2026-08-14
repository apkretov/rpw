#pragma once

#pragma region MINE

#include "simulated_duration.h"
#include <format>
#include <string>
#include <thread>

struct Database {
	std::string query(int id) const {
		std::this_thread::sleep_for(simulated_duration);
		return std::format("item-{}", id);
	}
};
#pragma endregion //MINE
