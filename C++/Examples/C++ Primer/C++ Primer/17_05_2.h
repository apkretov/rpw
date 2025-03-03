#pragma once

#pragma region EX_17_37

#include <fstream>
#include <iostream>
#include <string>

void read_file(const std::string &path, char delim) {
	std::ifstream is(path);
	if (!is.is_open()) 
		throw std::ios_base::failure("Failed to open file: " + path);
	
	constexpr size_t size = 1024;
	while (is.good() && !is.eof()) {
		char sink[size];
		is.getline(sink, size, delim);
		std::string line = sink;
		std::cout << line << '\n';
	}
}
#pragma endregion
