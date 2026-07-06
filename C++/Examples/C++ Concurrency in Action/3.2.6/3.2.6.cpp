#ifndef MINE

#include "Listing 3.9.h"
#include "../../stdafx.h"

int main() {
	print_file_line();

	X x1(10);
	X x2(20);

	std::cout << "Before: x1=" << x1.get_value() << ", x2=" << x2.get_value() << std::endl;

	swap(x1, x2);
	std::cout << "After unique_lock: x1=" << x1.get_value() << ", x2=" << x2.get_value() << std::endl;

	swap_scoped(x1, x2);
	std::cout << "After scoped: x1=" << x1.get_value() << ", x2=" << x2.get_value() << std::endl;

	return 0;
}
#endif //MINE
