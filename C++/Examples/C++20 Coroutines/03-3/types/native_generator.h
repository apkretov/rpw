#pragma region MINE
#pragma once

#include "types/native_generator_promise.h"
#include "types/trace.h"
#include <coroutine>
#include <utility>

template <bool lazy_start, bool yield_suspends = true>
struct native_generator {
	using promise_type = native_generator_promise<lazy_start, yield_suspends>;

	native_generator() = default;
	explicit native_generator(std::coroutine_handle<promise_type> handle_) : handle(handle_) {}
	native_generator(const native_generator&) = delete;
	native_generator& operator=(const native_generator&) = delete;
	native_generator(native_generator&& other) noexcept : handle(other.handle) { other.handle = {}; }

	native_generator& operator=(native_generator&& other) noexcept {
		if (this != &other) {
			destroy();
			handle = other.handle;
			other.handle = {};
		}
		return *this;
	}

	~native_generator() { destroy(); }

	bool done() const { return !handle || handle.done() || handle.promise().done; }
	int value() const { return handle ? handle.promise().current_value : 0; }

	void resume() {
		if (handle && !handle.done())
			handle.resume();
	}

	bool next() {
		if (!handle || done())
			return false;
		resume();
		return !done();
	}

	void destroy() {
		if (handle) {
			handle.destroy();
			handle = {};
		}
	}
private:
	std::coroutine_handle<promise_type> handle{};
};

template <bool lazy_start, bool yield_suspends>
native_generator<lazy_start, yield_suspends>
native_generator_promise<lazy_start, yield_suspends>::get_return_object() {
	trace_log(trace_mode::native, "[Promise:get_return_object]");
	return native_generator<lazy_start, yield_suspends>{
		std::coroutine_handle<native_generator_promise<lazy_start, yield_suspends>>::from_promise(*this)};
}
#pragma endregion //MINE
