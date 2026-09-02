#pragma region MINE
#pragma once

#include "types/native_coroutine_result.h"
#include "types/native_task_promise.h"
#include "types/native_task_void_promise.h"
#include "types/trace.h"
#include <coroutine>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class native_task {
public:
	using promise_type = native_task_promise<T>;

	native_task() = default;

	native_task(const native_task&) = delete;
	native_task& operator=(const native_task&) = delete;

	native_task(native_task&& other) noexcept
		: handle(std::exchange(other.handle, {})), result(std::move(other.result)) {}

	native_task& operator=(native_task&& other) noexcept {
		if (this != &other) {
			destroy();
			handle = std::exchange(other.handle, {});
			result = std::move(other.result);
		}
		return *this;
	}

	~native_task() { destroy(); }

	bool ready() const { return result && result->ready; }

	T get() {
		if (!result)
			throw std::runtime_error("invalid native task");
		T value = result->get();
		destroy();
		return value;
	}

	bool await_ready() const { return result && result->ready; }

	bool await_suspend(std::coroutine_handle<> continuation) {
		if (await_ready())
			return false;
		continuation_ = continuation;
		return true;
	}

	T await_resume() {
		trace_log(trace_mode::native, "[Awaitable:await_resume]", "nested value received");
		return get();
	}

private:
	friend struct native_task_promise<T>;

	explicit native_task(std::coroutine_handle<promise_type> h,
		std::shared_ptr<native_coroutine_result<T>> r)
		: handle(h), result(std::move(r)) {}

	void destroy() {
		if (handle) {
			handle.destroy();
			handle = {};
		}
	}

	std::coroutine_handle<promise_type> handle{};
	std::shared_ptr<native_coroutine_result<T>> result;
	std::coroutine_handle<> continuation_{};
};

template <>
class native_task<void> {
public:
	using promise_type = native_task_void_promise;

	native_task() = default;

	native_task(const native_task&) = delete;
	native_task& operator=(const native_task&) = delete;

	native_task(native_task&& other) noexcept
		: handle(std::exchange(other.handle, {})), result(std::move(other.result)) {}

	native_task& operator=(native_task&& other) noexcept {
		if (this != &other) {
			destroy();
			handle = std::exchange(other.handle, {});
			result = std::move(other.result);
		}
		return *this;
	}

	~native_task() { destroy(); }

	bool ready() const { return result && result->ready; }

	void get() {
		if (!result)
			throw std::runtime_error("invalid native task");
		result->get();
		destroy();
	}

private:
	friend struct native_task_void_promise;

	explicit native_task(std::coroutine_handle<promise_type> h,
		std::shared_ptr<native_coroutine_result<void>> r)
		: handle(h), result(std::move(r)) {}

	void destroy() {
		if (handle) {
			handle.destroy();
			handle = {};
		}
	}

	std::coroutine_handle<promise_type> handle{};
	std::shared_ptr<native_coroutine_result<void>> result;
};

template <typename T>
native_task<T> native_task_promise<T>::get_return_object() {
	trace_log(trace_mode::native, "[Promise:get_return_object]");
	return native_task<T>{
		std::coroutine_handle<native_task_promise<T>>::from_promise(*this), result};
}

inline native_task<void> native_task_void_promise::get_return_object() {
	trace_log(trace_mode::native, "[Promise:get_return_object]");
	return native_task<void>{
		std::coroutine_handle<native_task_void_promise>::from_promise(*this), result};
}
#pragma endregion //MINE
