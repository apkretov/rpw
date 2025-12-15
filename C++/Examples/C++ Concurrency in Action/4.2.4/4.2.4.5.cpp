#ifdef MINE

#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "../../stdafx.h"
#include "calculate_value.h"
using namespace std;

int main() { // promise with make_exception_ptr
	print_file_line();

	promise<double> some_promise;
	future<double> f = some_promise.get_future();

	jthread worker([&some_promise] {
		try {
			some_promise.set_value(calculate_value());
		}
		catch (const out_of_range&) {
			some_promise.set_exception(make_exception_ptr(out_of_range("vector.at() out of range"))); // Creates a known exception pointer without rethrowing, and stores it directly — avoiding current_exception() overhead.
		}
	});

	try {
		double result = f.get();
		cout << "Result: " << result << endl;
	}
	catch (const out_of_range& e) {
		cout << "Direct exception from vector.at(): " << e.what() << endl;
	}
}
#endif //MINE