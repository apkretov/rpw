#include <cassert>
#include <iostream>
#include "experimental_future.h" // Cause: #include <experimental/future> failed because MSVC does not provide that header. Fix: Added a local teaching header as experimental_future.h (same pattern as simple_future stubs).
#include "../../stdafx.h"

static std::experimental::future<int> find_the_answer() { return std::experimental::make_ready_future(42); } //MINE

static int find_the_question(std::experimental::future<int> the_answer) { return the_answer.get(); } //MINE

int main() {
	print_file_line();

	auto fut = find_the_answer();
	auto fut2 = fut.then(find_the_question);
	assert(!fut.valid());
	assert(fut2.valid());
	
	std::cout << AS_KV(fut2.get()) << '\n'; //MINE

	return 0;
}
