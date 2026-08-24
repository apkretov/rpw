#pragma once

#pragma region MINE

#include "async_simulator.h"
#include <format>
#include <string>

struct Database {
	auto async_query(int id) const {
		return simulate_async("async_query", [id] {
			return std::format("item-{}", id);
		});
	}
};
#pragma endregion //MINE
