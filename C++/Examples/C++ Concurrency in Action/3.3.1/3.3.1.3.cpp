#if 0

#include <memory>
#include <mutex>
#include <thread>
#include <iostream>
#include "../../stdafx.h"

struct some_resource {
	void do_something() {}
};

std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;

void init_resource() { resource_ptr.reset(new some_resource); }

void foo() {
	std::call_once(resource_flag, init_resource);
	resource_ptr->do_something();
}

int main() {
	print_file_line();

	std::thread t1(foo);
	std::thread t2(foo);
	t1.join();
	t2.join();
}
#endif //1