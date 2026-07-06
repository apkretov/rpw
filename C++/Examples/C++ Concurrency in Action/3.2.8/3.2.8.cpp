#ifndef MINE // The author skipped an example for Listing 3.6.h. Generate one — I'll experiment with it.

#include "Listing 3.10.h"
#include "../../stdafx.h"

int main() {
	print_file_line();

	Y y1(10);
	Y y2(20);

	std::cout << "y1=" << y1.get_value() << ", y2=" << y2.get_value() << '\n';
	std::cout << "y1 == y2: " << (y1 == y2 ? "true" : "false") << '\n';

	return 0;
}
#endif //MINE
