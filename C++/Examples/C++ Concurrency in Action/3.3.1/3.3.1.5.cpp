#if 1

#include <print>
#include <thread>
#include "../../stdafx.h"

class my_class {
public:
	my_class() { std::print("Thread {}: my_class constructor called once\n", std::this_thread::get_id()); } //MINE
};

my_class& get_my_class_instance() {
	std::print("Thread {}: implementing get_my_class_instance()\n", std::this_thread::get_id());
	static my_class instance; // Initialization guaranteed to be thread-safe
	return instance;
}

int main() {
	print_file_line();

	std::jthread t1(get_my_class_instance);
	std::jthread t2(get_my_class_instance);

	return 0;
}
#endif //1
