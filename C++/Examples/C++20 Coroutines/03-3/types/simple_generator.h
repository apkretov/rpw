#pragma region MINE
#pragma once

#include "types/simple_generator_frame.h"

struct simple_generator {
	simple_generator_frame* frame = nullptr;
	bool eager_start = false;

	simple_generator() = default;
	explicit simple_generator(simple_generator_frame* f, bool eager) : frame(f), eager_start(eager) {}
	simple_generator(const simple_generator&) = delete;
	simple_generator& operator=(const simple_generator&) = delete;

	simple_generator(simple_generator&& other) noexcept
		: frame(other.frame), eager_start(other.eager_start) {
		other.frame = nullptr;
	}

	simple_generator& operator=(simple_generator&& other) noexcept {
		if (this != &other) {
			destroy();
			frame = other.frame;
			eager_start = other.eager_start;
			other.frame = nullptr;
		}
		return *this;
	}

	~simple_generator() { destroy(); }

	bool done() const {
		return frame == nullptr || frame->promise.done;
	}

	int value() const {
		return frame != nullptr ? frame->promise.current_value : 0;
	}

	void resume() {
		if (frame != nullptr && !frame->at_final_suspend)
			frame->resume();
	}

	bool next() {
		if (frame == nullptr || done())
			return false;
		resume();
		return !done();
	}

	void destroy() {
		if (frame != nullptr) {
			if (frame->at_final_suspend && !frame->finished)
				frame->resume();
			frame->destroy();
			frame = nullptr;
		}
	}
};
#pragma endregion //MINE
