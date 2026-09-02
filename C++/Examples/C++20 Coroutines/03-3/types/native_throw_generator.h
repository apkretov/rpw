#pragma region MINE
#pragma once

#include "types/native_throw_generator_promise.h"
#include "types/trace.h"
#include <coroutine>
#include <utility>

struct native_throw_generator {
	using promise_type = native_throw_generator_promise;

	explicit native_throw_generator(std::coroutine_handle<promise_type> handle_) : handle(handle_) {}
	native_throw_generator(native_throw_generator&& other) noexcept : handle(other.handle) { other.handle = {}; }
	native_throw_generator(const native_throw_generator&) = delete;
	native_throw_generator& operator=(const native_throw_generator&) = delete;
	native_throw_generator& operator=(native_throw_generator&&) = delete;

	~native_throw_generator() {
		if (handle)
			handle.destroy();
	}

	bool done() const { return !handle || handle.promise().done; }
	int value() const { return handle ? handle.promise().current_value : 0; }

	void resume() {
		if (handle && !handle.done())
			handle.resume();
	}
private:
	std::coroutine_handle<promise_type> handle{};
};

inline native_throw_generator native_throw_generator_promise::get_return_object() {
	trace_log(trace_mode::native, "[Promise:get_return_object]");
	return native_throw_generator{
		std::coroutine_handle<native_throw_generator_promise>::from_promise(*this)};
}
#pragma endregion //MINE
