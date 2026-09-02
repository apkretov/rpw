#include "connection.h"
#include "database.h"
#include "handle_request_frame.h"
#include "task.h"
#include "simple_co_await.h"
#include "simple_suspend_never.h"
#include "../../stdafx.h"

#include <format>
#include <print>
#include <thread>

Database database;

#pragma region MINE

static void handle_request_destroy(simple_coroutine_frame* base) {
	delete static_cast<handle_request_frame*>(base);
}

// Hand-written resume state machine equivalent to 01-3's handle_request body.
static void handle_request_resume(simple_coroutine_frame* base) {
	auto* frame = static_cast<handle_request_frame*>(base);

	switch (frame->state_index) {
	case 0: {
		// initial_suspend = never -- run body immediately at ramp.
		simple_suspend_never initial{};
		if (simple_co_await(frame, 0, initial, [] {}))
			return;

		std::println("{} 222 handle_request: started...", std::this_thread::get_id());

		frame->read_await.emplace(frame->conn->async_read());
		if (simple_co_await(frame, 1, *frame->read_await, [] {}))
			return;
		frame->state_index = 1;
		[[fallthrough]];
	}

	case 1: {
		frame->request = frame->read_await->await_resume();
		frame->read_await.reset();

		frame->parsed = parse_request(frame->request);

		frame->query_await.emplace(database.async_query(frame->parsed.id));
		if (simple_co_await(frame, 2, *frame->query_await, [] {}))
			return;
		frame->state_index = 2;
		[[fallthrough]];
	}

	case 2: {
		frame->data = frame->query_await->await_resume();
		frame->query_await.reset();

		frame->response = compute_response(frame->data);

		frame->write_await.emplace(frame->conn->async_write(frame->response));
		if (simple_co_await(frame, 3, *frame->write_await, [] {}))
			return;
		frame->state_index = 3;
		[[fallthrough]];
	}

	case 3: {
		frame->write_await->await_resume();
		frame->write_await.reset();

		std::println("{} 222 handle_request: completed (locals survived every co_await)", std::this_thread::get_id());

		// final_suspend: set done + notify, then suspend (frame kept alive for ready/get).
		{
			std::scoped_lock lock(frame->mutex);
			frame->done = true;
		}
		frame->cv.notify_one();
		frame->state_index = 4;
		return;
	}

	case 4: {
		frame->finished = true;
		return;
	}

	default:
		return;
	}
}

task handle_request(connection& conn) {
	auto* frame = new handle_request_frame{};
	frame->resume_fn = handle_request_resume;
	frame->destroy_fn = handle_request_destroy;
	frame->conn = &conn;
	frame->resume(); // get_return_object + initial_suspend=never
	return task{frame};
}

int main() {
	print_file_line();

	std::println("{} 111 main thread = {}", std::this_thread::get_id(), std::this_thread::get_id());

	connection conn;
	auto t = handle_request(conn);
	std::println("{} 555/444 handle_request returned at first co_await", std::this_thread::get_id());

	LogDuration ld(std::format("{} 666 main waiting for coroutine", std::this_thread::get_id()));
	while (!t.ready()) {
		std::println("{} 777   [main] waiting for ~200ms...", std::this_thread::get_id());
		std::this_thread::sleep_for(200ms);
	}
	t.get();

	return 0;
}
#pragma endregion //MINE
