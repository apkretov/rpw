#pragma once

#pragma region MINE

#include "async_simulator.h"
#include <print>
#include <string>

struct connection {
	auto async_read() const {
		return simulate_async("async_read", [] { return std::string("42"); });
	}

	auto async_write(std::string response) const {
		return simulate_async("async_write", [response = std::move(response)] {
			std::println("{}", response);
		});
	}
};
#pragma endregion //MINE
