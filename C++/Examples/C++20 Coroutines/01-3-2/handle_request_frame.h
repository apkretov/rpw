#pragma once

#pragma region MINE

#include "async_simulator.h"
#include "parsed_request.h"
#include "task_frame.h"
#include <optional>
#include <string>

struct connection;

// Locals that would live in the compiler-generated coroutine frame across every co_await.
struct handle_request_frame : task_frame {
	connection* conn = nullptr;
	std::string request;
	parsed_request parsed{};
	std::string data;
	std::string response;

	// Awaitables must outlive suspend (worker thread holds `this` until resume).
	std::optional<async_awaitable<std::string>> read_await;
	std::optional<async_awaitable<std::string>> query_await;
	std::optional<async_awaitable<void>> write_await;
};
#pragma endregion //MINE
