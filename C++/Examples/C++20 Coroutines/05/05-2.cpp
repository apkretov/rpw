#if 1

#include <iostream>
#include "05.h"
#include "../../stdafx.h"

Generator fibonacci() {
	int a = 0, b = 1;
	while (true) {
		co_yield a;
		int next = a + b;
		a = b;
		b = next;
	}
}

int main() {
	print_file_line();

	auto fib = fibonacci();

	for (int i = 0; i < 10 && fib.next(); ++i) {
		std::cout << fib.value() << " ";
	}
	std::cout << std::endl;
}
#endif // 1
