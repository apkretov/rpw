#pragma once

#pragma region MINE

#include <string>

struct parsed_request {
	int id;
};

parsed_request parse_request(const std::string& request) { return {std::stoi(request)}; }

std::string compute_response(const std::string& data) { return "200 OK " + data; }
#pragma endregion //MINE