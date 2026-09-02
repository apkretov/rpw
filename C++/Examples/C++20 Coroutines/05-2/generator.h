#pragma once

#pragma region MINE

#include "generator_frame.h"
#include <utility>

// Move-only lazy generator wrapper analogous to 05's Generator.
class Generator {
public:
	explicit Generator(generator_frame* f) : frame(f) {}

	Generator(const Generator&) = delete;
	Generator& operator=(const Generator&) = delete;

	Generator(Generator&& other) noexcept : frame(std::exchange(other.frame, nullptr)) {}

	Generator& operator=(Generator&& other) noexcept {
		if (this != &other) {
			destroy();
			frame = std::exchange(other.frame, nullptr);
		}
		return *this;
	}

	~Generator() { destroy(); }

	bool next() {
		if (!frame || frame->finished)
			return false;
		frame->resume();
		return frame && !frame->finished;
	}

	int value() const {
		return frame->current_value;
	}

private:
	void destroy() {
		if (frame) {
			frame->destroy();
			frame = nullptr;
		}
	}

	generator_frame* frame = nullptr;
};

Generator count_to(int n);
#pragma endregion //MINE
