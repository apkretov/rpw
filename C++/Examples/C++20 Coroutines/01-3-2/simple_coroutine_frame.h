#pragma once

#pragma region MINE

// Hand-rolled stand-in for a compiler-generated coroutine frame (no C++20 coroutine keywords).
struct simple_coroutine_frame {
	int state_index = 0;
	bool finished = false;

	void (*resume_fn)(simple_coroutine_frame*) = nullptr;
	void (*destroy_fn)(simple_coroutine_frame*) = nullptr;

	void resume() {
		if (finished || resume_fn == nullptr)
			return;
		resume_fn(this);
	}

	void destroy() {
		if (destroy_fn == nullptr)
			return;
		destroy_fn(this);
		destroy_fn = nullptr;
		resume_fn = nullptr;
	}
};
#pragma endregion //MINE
