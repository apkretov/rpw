#ifdef MINE

#include <future>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() { // Broken promise
	print_file_line();

	future<int> f;
	{
		promise<int> p;
		f = p.get_future();
	} // Destroy promise without setting value/exception. p destructor stores broken_promise.

	try {
		int res = f.get();
		cout << "res = " << res << '\n';
	}
	catch (const future_error& e) {
		cerr << "Broken promise: " << e.what() << '\n';
	}
}
#endif //MINE
