#pragma once

#pragma region MINE

#include "async_simulator.h"
#include <format>
#include <string>

struct Database {
	template<typename Callback>
	void async_query(int id, Callback callback) const {
		simulate_async("async_query", [id, callback = std::move(callback)] {
			callback(std::format("item-{}", id));
		});
	}
};
#pragma endregion //MINE
