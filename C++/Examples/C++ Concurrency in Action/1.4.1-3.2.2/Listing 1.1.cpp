#if 0

#include <iostream>
#include <thread>
#include "../../stdafx.h"

void hello() { std::cout << "Hello Concurrent World\n"; }

int main() {
	print_file_line();
	
	std::thread t(hello);
	t.join();
}
#endif // 1
