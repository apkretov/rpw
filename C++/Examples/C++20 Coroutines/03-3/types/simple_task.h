#pragma region MINE
#pragma once

#include "types/simple_manual_awaitable.h"
#include "types/simple_task_int_frame.h"
#include "types/simple_task_void_frame.h"
#include <stdexcept>

template <typename result_t>
struct simple_task;

template <>
struct simple_task<int> {
	simple_task_int_frame* frame = nullptr;

	simple_task() = default;
	explicit simple_task(simple_task_int_frame* f) : frame(f) {}

	simple_task(const simple_task&) = delete;
	simple_task& operator=(const simple_task&) = delete;

	simple_task(simple_task&& other) noexcept : frame(other.frame) {
		other.frame = nullptr;
	}

	simple_task& operator=(simple_task&& other) noexcept {
		if (this != &other) {
			destroy();
			frame = other.frame;
			other.frame = nullptr;
		}
		return *this;
	}

	~simple_task() { destroy(); }

	bool ready() const { return frame != nullptr && frame->result.ready; }

	int get() {
		if (frame == nullptr)
			throw std::runtime_error("invalid simple task");
		int value = frame->result.get();
		destroy();
		return value;
	}

	simple_manual_awaitable* manual_awaitable() {
		return frame != nullptr ? &frame->manual_awaitable : nullptr;
	}

	void destroy() {
		if (frame != nullptr) {
			if (!frame->finished && frame->state_index >= 1)
				frame->resume();
			frame->destroy();
			frame = nullptr;
		}
	}
};

template <>
struct simple_task<void> {
	simple_task_void_frame* frame = nullptr;

	simple_task() = default;
	explicit simple_task(simple_task_void_frame* f) : frame(f) {}

	simple_task(const simple_task&) = delete;
	simple_task& operator=(const simple_task&) = delete;

	simple_task(simple_task&& other) noexcept : frame(other.frame) {
		other.frame = nullptr;
	}

	simple_task& operator=(simple_task&& other) noexcept {
		if (this != &other) {
			destroy();
			frame = other.frame;
			other.frame = nullptr;
		}
		return *this;
	}

	~simple_task() { destroy(); }

	bool ready() const { return frame != nullptr && frame->result.ready; }

	void get() {
		if (frame == nullptr)
			throw std::runtime_error("invalid simple task");
		frame->result.get();
		destroy();
	}

	simple_manual_awaitable* manual_awaitable() {
		return frame != nullptr ? &frame->manual_awaitable : nullptr;
	}

	void destroy() {
		if (frame != nullptr) {
			if (!frame->finished && frame->state_index >= 1)
				frame->resume();
			frame->destroy();
			frame = nullptr;
		}
	}
};

inline simple_coroutine_frame* simple_manual_await_target(simple_task<void>& task) {
	if (auto* awaitable = task.manual_awaitable())
		return awaitable->stored_frame;
	return nullptr;
}

inline simple_coroutine_frame* simple_manual_await_target(simple_task<int>& task) {
	if (auto* awaitable = task.manual_awaitable())
		return awaitable->stored_frame;
	return nullptr;
}
#pragma endregion //MINE
