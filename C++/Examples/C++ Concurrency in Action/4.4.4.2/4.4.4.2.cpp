#if 1

#pragma region MINE

#include <chrono>
#include <print>
#include <string>
#include <thread>
#include "../4.4.3/Listing 4.17.h"
#include "../../stdafx.h"

using namespace std::chrono_literals;

struct some_data {
	int value;
	std::string message;
};

static some_data some_function() {
	std::println("Producer: starting one shared operation...");
	std::this_thread::sleep_for(200ms);
	std::println("Producer: result is ready.");
	return {42, "shared result"};
}

static void do_stuff(std::experimental::shared_future<some_data> data) {
	auto const& result = data.get();
	std::println("Continuation 1: value = {}", result.value);
}

static std::string do_other_stuff(std::experimental::shared_future<some_data> data) {
	auto const& result = data.get();
	std::println("Continuation 2: message = {}", result.message);
	return result.message;
}
#pragma endregion //MINE

int main() {
	print_file_line();

	auto fut = spawn_async(some_function).share();
	auto fut2 = fut.then([](std::experimental::shared_future<some_data> data) {
		do_stuff(data);
	});
	auto fut3 = fut.then([](std::experimental::shared_future<some_data> data) {
		return do_other_stuff(data);
	});

	#pragma region MINE
	fut2.get();
	std::println("fut3 returned: {}", fut3.get());
	std::println("Both continuations consumed the same shared result.");
	#pragma endregion //MINE

	return 0;
}
#endif //1