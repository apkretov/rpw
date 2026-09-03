#pragma once

#pragma region MINE

#include "simple_coroutine_frame.h"
#include <iostream>
#include <thread>

struct Awaiter { // Hand-rolled stand-in for 03-1's Awaiter; stores a frame* instead of coroutine_handle.
	simple_coroutine_frame** handle_out = nullptr;

	bool await_ready() {
		std::cout << std::this_thread::get_id() << " 444 await_ready()" << std::endl;
		return false;
	}

	bool await_suspend(simple_coroutine_frame* frame) {
		std::cout << std::this_thread::get_id() << " 555 await_suspend()" << std::endl;
		*handle_out = frame;
		return true; // void await_suspend => always suspend
	}

	void await_resume() { std::cout << std::this_thread::get_id() << " 777 await_resume()" << std::endl; }
};
#pragma endregion //MINE
