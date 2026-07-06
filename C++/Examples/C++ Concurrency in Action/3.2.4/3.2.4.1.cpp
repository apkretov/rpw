#ifdef MINE // The author skipped an example for Listing 3.6.h. Generate one — I'll experiment with it.

#include "Listing 3.6.h"
#include "../../stdafx.h"

int main() {
	print_file_line();

	X x1(10);
	X x2(20);

	std::cout << "Before swap: x1=" << x1.get_value() << ", x2=" << x2.get_value() << std::endl;

	swap(x1, x2); // Test original version
	std::cout << "After original: x1=" << x1.get_value() << ", x2=" << x2.get_value() << std::endl;

	swap_scoped(x1, x2); // Test C++17 version
	std::cout << "After scoped: x1=" << x1.get_value() << ", x2=" << x2.get_value() << std::endl;

	return 0;
}
#endif //MINE
