#ifdef MINE

#include <future>
#include <iostream>
#include <thread>
#include "../../stdafx.h"
#include "calculate_value.h"
using namespace std;

int main() { // promise with try/catch
	print_file_line();

	promise<double> some_promise;
	future<double> f = some_promise.get_future();

	jthread worker([&some_promise] {
		try {
			some_promise.set_value(calculate_value());
		}
		catch (const out_of_range&) {
			some_promise.set_exception(current_exception());
		}
	});

	try {
		double result = f.get();
		cout << "Result: " << result << endl;
	}
	catch (const out_of_range& e) {
		cout << "Promise caught vector.at() error: " << e.what() << endl;
	}
}
#endif //MINE