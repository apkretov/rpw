#if 0

#include <thread>
#include "../../stdafx.h"
#include "Listing 2.1.h"

class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) : t(t_) {}

	~thread_guard() {
		if (t.joinable())
			t.join();
	}
	
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};

struct func;

void do_something_in_current_thread() {/**/} //MINE

void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
}

int main() {
	print_file_line();
	f();
}
#endif //1