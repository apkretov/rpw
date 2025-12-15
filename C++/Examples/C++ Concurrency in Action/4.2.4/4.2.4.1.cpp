#ifdef MINE

#include <iostream>
#include <stdexcept>
#include "../../stdafx.h"
#include "square_root.h"
using namespace std;

int main() { // Direct call throws immediately.
	print_file_line();

	try {
		double y = square_root(-1);  // Throws out_of_range
		cout << "Result: " << y << '\n';
	}
	catch (const out_of_range& e) {
		cerr << "Caught: " << e.what() << '\n';
	}
}
#endif //MINE