#ifdef MINE

#include <future>
#include <iostream>
#include <stdexcept>
#include "../../stdafx.h"
#include "square_root.h"
using namespace std;

int main() { // std::async Exception Storage
	print_file_line();

	future<double> f = async(square_root, -1);
	try {
		double y = f.get();  // Rethrows stored out_of_range
		cout << "Result: " << y << '\n';
	}
	catch (const out_of_range& e) {
		cerr << "Rethrew from future: " << e.what() << '\n';
	}
}
#endif //MINE