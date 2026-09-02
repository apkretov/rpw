#pragma once

#pragma region MINE

#include <format>
#include <string>
#include <thread>

struct parsed_request {
	int id;
};

parsed_request parse_request(const std::string& request) { return {std::stoi(request)}; }

std::string compute_response(const std::string& data) {
	return std::format("{} 999 200 OK {}", std::this_thread::get_id(), data);
}
#pragma endregion //MINE
