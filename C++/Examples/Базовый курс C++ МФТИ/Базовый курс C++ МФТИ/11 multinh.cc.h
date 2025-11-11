//@https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/multinh.cc

#include <iostream>
#include <stdexcept>
#include "stdafx.h"
using namespace std;

#if 1
struct my_exc1 : std::exception {
	char const* what() const noexcept override { return "exc1"; }
};

struct my_exc2 : std::exception {
	char const* what() const noexcept override { return "exc2"; }
};

struct your_exc3 : my_exc1, my_exc2 {};

int main() {
	PRINT_FILE_LINE();
	try {
		throw your_exc3();
	}
	catch (std::exception const& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "whoops!\n";
	}
}
#endif // 1

#if 0
struct my_exc1 : virtual exception {
	char const* what() const noexcept override { return "exc1"; }
};

struct my_exc2 : virtual exception {
	char const* what() const noexcept override { return "exc2"; }
};

struct your_exc3 : my_exc1, my_exc2 {
	char const* what() const noexcept override { return "your_exc3"; } //TEST!  
};

int main() {
	PRINT_FILE_LINE();

	try {
		throw your_exc3();
	}
	catch (exception const& e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cerr << "whoops!\n";
	}
}
#endif

#ifdef MINE
#include <iostream>
using namespace std;

struct Base {
	virtual ~Base() = default;
	virtual const char* what() const noexcept {
		return "Base";
	}
};

struct my_exc1 : virtual Base {};
struct my_exc2 : virtual Base {};
struct your_exc3 : my_exc1, my_exc2 {}; //TEST

int main() {
	PRINT_FILE_LINE();

	try {
		throw your_exc3();
	}
	catch (const Base& e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cerr << "whoops!\n";
	}
}
#endif
