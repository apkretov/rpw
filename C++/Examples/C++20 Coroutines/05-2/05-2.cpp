#include "generator.h"
#include "simple_co_await.h"
#include "simple_suspend_always.h"
#include "../../stdafx.h"

#include <iostream>

#pragma region MINE

static void count_to_destroy(simple_coroutine_frame* base) {
	delete static_cast<generator_frame*>(base);
}

// Hand-written resume state machine equivalent to 05's count_to body.
static void count_to_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<generator_frame*>(base);

	switch (frame->state_index) {
	case 0: {
		// Past initial_suspend=always (first next() resumes here).
		frame->i = 1;
		if (frame->i > frame->n) {
			frame->finished = true;
			frame->state_index = 2;
			return;
		}

		// co_yield i  => yield_value stores int, then suspend_always
		frame->current_value = frame->i;
		{
			simple_suspend_always yield_suspend{};
			if (simple_co_await(frame, 1, yield_suspend, [] {}))
				return;
		}
		frame->state_index = 1;
		[[fallthrough]];
	}

	case 1: {
		++frame->i;
		if (frame->i > frame->n) {
			// return_void + final_suspend=always
			frame->finished = true;
			frame->state_index = 2;
			return;
		}

		frame->current_value = frame->i;
		{
			simple_suspend_always yield_suspend{};
			if (simple_co_await(frame, 1, yield_suspend, [] {}))
				return;
		}
		return;
	}

	case 2: {
		return;
	}

	default:
		return;
	}
}

Generator count_to(int n) {
	auto* frame = new generator_frame{};
	frame->resume_fn = count_to_resume;
	frame->destroy_fn = count_to_destroy;
	frame->n = n;
	// initial_suspend = always: do not resume yet (lazy generator).
	return Generator{frame};
}

int main() {
	print_file_line();

	auto gen = count_to(5);

	while (gen.next()) {
		std::cout << gen.value() << std::endl;
	}
}

#pragma endregion //MINE
