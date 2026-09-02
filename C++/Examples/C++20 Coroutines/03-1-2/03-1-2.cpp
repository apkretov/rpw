#include "counter_frame.h"
#include "return_object.h"
#include "simple_co_await.h"
#include "simple_suspend_never.h"
#include "../../stdafx.h"

#include <iostream>
#include <thread>
#include <vector>

#pragma region MINE

static void counter_destroy(simple_coroutine_frame* base) {
	delete static_cast<counter_frame*>(base);
}

// Hand-written resume state machine equivalent to 03-1's counter body.
static void counter_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<counter_frame*>(base);

	switch (frame->state_index) {
	case 0: {
		// initial_suspend = never -- run body immediately at ramp.
		std::cout << std::this_thread::get_id() << " 222 initial_suspend()" << std::endl;
		simple_suspend_never initial{};
		if (simple_co_await(frame, 0, initial, [] {}))
			return;

		frame->i = 0;
		frame->awaiter = Awaiter{frame->handle_out};

		std::cout << '\n' << std::this_thread::get_id() << " 333 counter: " << frame->i << std::endl;
		if (simple_co_await(frame, 1, frame->awaiter, [] {}))
			return;
		frame->state_index = 1;
		[[fallthrough]];
	}

	case 1: {
		frame->awaiter.await_resume();
		++frame->i;

		if (frame->i >= 3) {
			std::cout << std::this_thread::get_id() << " 888 return_void()" << std::endl;
			std::cout << std::this_thread::get_id() << " 999 final_suspend()" << std::endl;
			// final_suspend = never => compiler destroys the frame before resume returns.
			frame->finished = true;
			auto* dfn = frame->destroy_fn;
			frame->destroy_fn = nullptr;
			frame->resume_fn = nullptr;
			dfn(frame);
			return;
		}

		std::cout << '\n' << std::this_thread::get_id() << " 333 counter: " << frame->i << std::endl;
		if (simple_co_await(frame, 1, frame->awaiter, [] {}))
			return;
		return;
	}

	default:
		return;
	}
}

ReturnObject counter(simple_coroutine_frame** handle_out) {
	auto* frame = new counter_frame{};
	frame->resume_fn = counter_resume;
	frame->destroy_fn = counter_destroy;
	frame->handle_out = handle_out;

	std::cout << std::this_thread::get_id() << " 111 get_return_object()" << std::endl;
	frame->resume(); // get_return_object + initial_suspend=never runs into first await
	return {};
}

int main() {
	print_file_line();

	simple_coroutine_frame* h = nullptr;
	simple_coroutine_frame* h2 = nullptr; // unused, preserved like 03-1
	std::vector v{0, 1, 2}; // unused, preserved like 03-1
	counter(&h);

	for (int i = 0; i < 3; ++i) {
		std::cout << '\n' << std::this_thread::get_id() << " 666 main: resuming" << std::endl;
		h->resume();
	}

	// Like 03-1: do not destroy — final_suspend=never already destroyed the frame.
}

#pragma endregion //MINE
