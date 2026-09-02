#pragma once

#pragma region MINE

#include "task_frame.h"
#include <mutex>
#include <utility>

struct connection;

class task {
public:
	explicit task(task_frame* f) : frame(f) {}

	task(const task&) = delete;
	task& operator=(const task&) = delete;

	task(task&& other) noexcept : frame(std::exchange(other.frame, nullptr)) {}

	task& operator=(task&& other) noexcept {
		if (this != &other) {
			destroy();
			frame = std::exchange(other.frame, nullptr);
		}
		return *this;
	}

	~task() { destroy(); }

	bool ready() const {
		std::scoped_lock lock(frame->mutex);
		return frame->done;
	}

	void get() {
		std::unique_lock lock(frame->mutex);
		frame->cv.wait(lock, [&] { return frame->done; });
		if (frame->exception)
			std::rethrow_exception(frame->exception);
	}

private:
	void destroy() {
		if (frame) {
			frame->destroy();
			frame = nullptr;
		}
	}

	task_frame* frame = nullptr;
};

task handle_request(connection& conn);
#pragma endregion //MINE
