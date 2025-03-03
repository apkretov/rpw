#pragma once

#include <chrono>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <source_location>
//#include <codecvt>

#ifndef OFF
// Keep this version for C++ standards prior to C++20.
#define PRINT_FILE_LINE() setlocale(LC_ALL, "RU"); \
						  std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n"
#endif

inline void print_file_line(const std::source_location &loc = std::source_location::current()) {
	(void *)(setlocale(LC_ALL, "RU"));
	std::cout << "File: " << loc.file_name() << "\tLine: " << loc.line() << "\n\n";
}

inline std::string format_num(int64_t num) { // Function to format the number with space as the thousands separator
	std::string numberStr = std::to_string(num);
	size_t len = numberStr.length();
	size_t separatorPos = len % 3;

	std::string formattedNumber;
	for (size_t i = 0; i < len; ++i) {
		if (i > 0 && (i - separatorPos) % 3 == 0)
			formattedNumber.push_back(' ');
		formattedNumber.push_back(numberStr.at(i));
	}

	return formattedNumber;
}

template <typename Resolution = std::chrono::microseconds, typename Function, typename... Args>
void duration(Function fnc, Args&&... args) {
	auto start = std::chrono::high_resolution_clock::now();
	fnc(std::forward<Args>(args)...);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<Resolution>(end - start);

	std::string unitName;
	if constexpr (std::is_same_v<Resolution, std::chrono::nanoseconds>) {
		unitName = "nanoseconds";
	} else if constexpr (std::is_same_v<Resolution, std::chrono::microseconds>) {
		unitName = "microseconds";
	} else if constexpr (std::is_same_v<Resolution, std::chrono::milliseconds>) {
		unitName = "milliseconds";
	} else if constexpr (std::is_same_v<Resolution, std::chrono::seconds>) {
		unitName = "seconds";
	} else if constexpr (std::is_same_v<Resolution, std::chrono::minutes>) {
		unitName = "minutes";
	} else if constexpr (std::is_same_v<Resolution, std::chrono::hours>) {
		unitName = "hours";
	} else {
		unitName = "unknown";
	}

	std::cout << "Execution time: " << format_num(duration.count()) << " " << unitName << '\n';
}

inline void view_file(const std::string &path) {
	std::fstream is(path);
	std::string file((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
	std::cout << file << '\n';
}

inline std::string log_str(const std::string_view msg, const std::source_location &loc = std::source_location::current()) {
	return format("\n{}\nFile: {} ({}:{})\nFunction: {}", msg, loc.file_name(), loc.line(), loc.column(), loc.function_name());
}

inline void log_by_clog(const std::string_view msg, const std::source_location &loc = std::source_location::current()) {
	std::clog << log_str(msg, loc) << '\n';
}
