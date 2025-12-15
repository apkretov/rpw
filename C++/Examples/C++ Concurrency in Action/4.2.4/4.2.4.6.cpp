#ifdef MINE

#include <future>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() { // Broken promise
	print_file_line();

	future<int>* f_ptr;
	{
		promise<int> p;
		future<int> f = p.get_future();
		f_ptr = &f;
	} // Destroy promise without setting value/exception. p destructor stores broken_promise.

	try {
		int res = f_ptr->get();  // Throws future_error(broken_promise)
	}
	catch (const future_error& e) {
		cerr << "Broken promise: " << e.what() << '\n';
	}
}
#endif //MINE
