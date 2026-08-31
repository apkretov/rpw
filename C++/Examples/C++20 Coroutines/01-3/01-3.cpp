#include "connection.h"
#include "database.h"
#include "parsed_request.h"
#include <string>
#include "task.h"
#include "vld.h"
#include "../../stdafx.h"

#include <format>
#include <print>
#include <thread>

Database database;

static task<void> handle_request(connection& conn) {
	std::println("{} 222 handle_request: started...", std::this_thread::get_id()); //MINE
	std::string request = co_await conn.async_read();
	auto parsed = parse_request(request);
	auto data = co_await database.async_query(parsed.id);
	auto response = compute_response(data);
	co_await conn.async_write(response);
	std::println("{} 222 handle_request: completed (locals survived every co_await)", std::this_thread::get_id()); //MINE
}

#pragma region MINE
int main() {
	print_file_line();

	std::println("{} 111 main thread = {}", std::this_thread::get_id(), std::this_thread::get_id());

	connection conn;
	auto t = handle_request(conn);
	std::println("{} 555/444 handle_request returned at first co_await", std::this_thread::get_id());

	LogDuration ld(std::format("{} 666 main waiting for coroutine", std::this_thread::get_id()));
	while (!t.ready()) {
		std::println("{} 777   [main] waiting for ~200ms...", std::this_thread::get_id());
		std::this_thread::sleep_for(200ms);
	}
	t.get();

	return 0;
}
#pragma endregion //MINE
