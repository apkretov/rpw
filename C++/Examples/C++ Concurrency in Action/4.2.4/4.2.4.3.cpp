#ifdef MINE

#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>
#include "../../stdafx.h"
#include "square_root.h"
using namespace std;

int main() { // packaged_task Example
	print_file_line();

	packaged_task<double(double)> task(square_root);
	future<double> f = task.get_future();

	jthread t(move(task), -1); // Run task in another thread

	try {
		double y = f.get();  // Rethrows stored exception
	}
	catch (const out_of_range& e) {
		cerr << "Packaged task rethrew: " << e.what() << '\n';
	}
}
#endif //MINE
