#pragma once

#include <algorithm>
#include <chrono>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <source_location> 
#include <vector>

#ifndef OFF__
// Keep this version for Russian source file names and C++ standards prior to C++20.
#define PRINT_FILE_LINE() static_cast<void>(setlocale(LC_ALL, "RU")); \
						  std::cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n"
#endif

#define AS_KV(x) #x << " = " << x

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) LogDuration UNIQ_ID(__LINE__) {message}

inline void print_file_line(const std::source_location &loc = std::source_location::current()) {
	static_cast<void>(setlocale(LC_ALL, "RU"));
	std::cout << "File: " << loc.file_name() << "\tLine: " << loc.line() << "\n\n";
}

inline std::string format_num(int64_t num) {
	std::string num_str = std::to_string(num);
	size_t len = num_str.length();
	std::string form_num;
	size_t first_group_sz = len % 3; // Size of the first group (if not a multiple of 3)

	if (first_group_sz > 0) { // Add the first group (if it exists)
		form_num += num_str.substr(0, first_group_sz);
		if (len > first_group_sz)
			form_num += " "; // Add space if there are more digits
	}

	for (size_t i = first_group_sz; i < len; i += 3) { // Add the remaining groups of three digits
		form_num += num_str.substr(i, 3);
		if (i + 3 < len)
			form_num += " "; // Add space if there are more digits
	}

	return form_num;
}

#ifdef KTB // Use the class below instead.
template <typename Resolution = std::chrono::microseconds, typename Function, typename... Args>
inline void duration(Function fnc, Args&&... args) {
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
#endif //KTB

template <typename Resolution = std::chrono::milliseconds>
class LogDuration {
public:
	explicit LogDuration(const std::string &msg = "") : message(msg) {
		std::cout << message << ": started..."  << std::endl;

		if constexpr (std::is_same_v<Resolution, std::chrono::nanoseconds>) { // Unlike doing this in the destructor, initialize unitName here to minimize exception prone operations.
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
	}

	LogDuration(const LogDuration &) = delete;
	LogDuration operator=(const LogDuration &) = delete;
	LogDuration(LogDuration &&) = delete;
	LogDuration operator=(LogDuration &&) = delete;

	~LogDuration() {
		try {
			finish = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<Resolution>(finish - start);
			std::cout << message << ": execution time = " << format_num(duration.count()) << " " << unitName << std::endl;
		}
		catch (const std::bad_alloc &e) {
			std::cerr << "Memory allocation failed while logging duration for: " << message	<< ". Error: " << e.what() << "\n";
		}
		catch (const std::exception &e) {
			std::cerr << "An error occurred while logging duration for: " << message << ". Error: " << e.what() << "\n";
		}
		catch (...) {
			std::cerr << "An unknown error occurred while logging duration for: " << message << ".\n";
		}
	}
private:
	const std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point finish;
	const std::string message;
	std::string unitName;
};

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

struct str_hash { // Custom transparent hasher for std::string
	/*
	std::size_t operator()(const std::string &str) const { return std::hash<std::string>{}(str); }
	std::size_t operator()(const char *str) const { return std::hash<std::string>{}(std::string(str)); }
	std::size_t operator()(const std::string_view &str) const { return std::hash<std::string>{}(std::string(str)); }
	*/
	std::size_t operator()(const std::string &str) const { return std::hash<std::string>{}(str); }
	template <typename T> std::size_t operator()(const T &str) const { return std::hash<std::string>{}(std::string(str)); } // Template-based transparent hasher for std::string
};

struct str_equal { // Custom transparent equality comparator for std::string
	/*
	bool operator()(const std::string &lhs, const std::string &rhs) const { return lhs == rhs; }
	bool operator()(const std::string &lhs, const char *rhs) const { return lhs == rhs; }
	bool operator()(const std::string &lhs, const std::string_view &rhs) const { return lhs == rhs; }
	bool operator()(const char *lhs, const std::string &rhs) const { return lhs == rhs; }
	bool operator()(const char *lhs, const char *rhs) const { return std::strcmp(lhs, rhs) == 0; }
	bool operator()(const char *lhs, const std::string_view &rhs) const { return lhs == rhs; }
	bool operator()(const std::string_view &lhs, const std::string &rhs) const { return lhs == rhs; }
	bool operator()(const std::string_view &lhs, const char *rhs) const { return lhs == rhs; }
	bool operator()(const std::string_view &lhs, const std::string_view &rhs) const { return lhs == rhs; }
	*/
	bool operator()(const char *lhs, const char *rhs) const { return std::strcmp(lhs, rhs) == 0; }
	template <typename T, typename U> bool operator()(const T &lhs, const U &rhs) const { return lhs == rhs; } // Template-based transparent equality comparator for std::string
};
