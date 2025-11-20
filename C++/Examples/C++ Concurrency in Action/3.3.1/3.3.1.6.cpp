#if 1

#include <iostream>
#include <thread>
#include "../../stdafx.h"
using namespace std;

class my_class {
public:
	my_class() { cout << "my_class constructor called once\n"; } //MINE
};

my_class& get_my_class_instance() {
	static my_class instance; // Initialization guaranteed to be thread-safe
	return instance;
}

int main() {
	print_file_line();

	thread t1(get_my_class_instance);
	thread t2(get_my_class_instance);

	t1.join();
	t2.join();

	return 0;
}
#endif //1
