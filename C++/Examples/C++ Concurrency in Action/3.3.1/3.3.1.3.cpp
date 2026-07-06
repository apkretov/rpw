#if 0

#include <memory>
#include <mutex>
#include <print>
#include <thread>
#include "../../stdafx.h"

struct some_resource { //MINE
	void do_something() { std::print("Thread {} called do_something()\n", std::this_thread::get_id()); }
};

std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;

void init_resource() { 
	print("Thread {} is initializing resource\n", std::this_thread::get_id()); //MINE
	resource_ptr.reset(new some_resource); 
}

void foo() {
	print("Thread {} called foo()\n", std::this_thread::get_id()); //MINE
	std::call_once(resource_flag, init_resource); // Initialization is called exactly once.
	resource_ptr->do_something();
}

int main() {
	print_file_line();

	std::jthread t1(foo);
	std::jthread t2(foo);
}
#endif //1