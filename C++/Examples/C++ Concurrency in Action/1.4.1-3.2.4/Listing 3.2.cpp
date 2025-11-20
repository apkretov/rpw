#if 0

#include <string>
#include <mutex>
#include "../../stdafx.h"
using namespace std;

class some_data {
	int a;
	std::string b;
public:
	void do_something() {}
};

class data_wrapper {
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func) {
		std::lock_guard<std::mutex> l(m);
		func(data); // ❶ Call user-supplied function with protected data
	}
};

some_data* unprotected;

void malicious_function(some_data& protected_data) { unprotected = &protected_data; } // Save pointer without protection

data_wrapper x;

void foo() {
	x.process_data(malicious_function); // ❷ Pass malicious function
	unprotected->do_something();        // ❸ Access protected data unprotected
}

int main() {
	print_file_line();

	//MINE
	foo();
	malicious_function(*unprotected);

	return 0;
}
#endif //1