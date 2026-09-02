#pragma region MINE
#pragma once

#include <exception>
#include <utility>

template <typename T>
struct native_coroutine_result {
	T value{};
	bool ready = false;
	bool has_exception = false;
	std::exception_ptr exception{};

	void set_value(const T& v) {
		value = v;
		ready = true;
	}

	void set_value(T&& v) {
		value = std::move(v);
		ready = true;
	}

	void set_exception(std::exception_ptr e) {
		exception = e;
		has_exception = true;
		ready = true;
	}

	T get() {
		if (has_exception)
			std::rethrow_exception(exception);
		return value;
	}
};

template <>
struct native_coroutine_result<void> {
	bool ready = false;
	bool has_exception = false;
	std::exception_ptr exception{};

	void set_value() { ready = true; }

	void set_exception(std::exception_ptr e) {
		exception = e;
		has_exception = true;
		ready = true;
	}

	void get() {
		if (has_exception)
			std::rethrow_exception(exception);
	}
};
#pragma endregion //MINE
