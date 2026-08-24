#pragma once

#pragma region MINE

#include "async_simulator.h"
#include <print>
#include <string>

struct connection {
	template<typename Callback>
	void async_read(Callback callback) const {
		simulate_async("async_read", [callback = std::move(callback)] { callback("42"); });
	}

	template<typename Callback>
	void async_write(const std::string& response, Callback callback) const {
		simulate_async("async_write", [response, callback = std::move(callback)] {
			std::println("{}", response);
			callback();
		});
	}
};
#pragma endregion //MINE
