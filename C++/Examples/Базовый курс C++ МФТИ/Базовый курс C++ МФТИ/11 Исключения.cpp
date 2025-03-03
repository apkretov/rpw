#include <iostream>
#include "stdafx.h"
using namespace std;

#ifdef _1
struct Base {
	virtual ~Base() {
		cout << "~Base()\n";
	}
};

struct Derived : Base {
	virtual ~Derived() {
		cout << "~Derived()\n";
	}
};

int main() {
	PRINT_FILE_LINE();

	try {
		throw Derived();
	}
	catch (Base b) { //TEST!
		cout << "catch (Base):\n";
	}
	catch (Derived d) {
		cout << "catch (Derived):\n";
	}
}
#endif

#ifdef _2
#include <iostream>
#include <stdexcept>
using namespace std;

struct my_exc1 : exception {
	char const *what() const noexcept override { return "exc1"; }
};

struct my_exc2 : exception {
	char const *what() const noexcept override { return "exc2"; }
};

struct your_exc3 : my_exc1, my_exc2 {};

int main() {
	PRINT_FILE_LINE();

	try {
		throw your_exc3();
	}
	catch (exception const &e) {
		cout << e.what() << endl;
	}
	catch (...) { //TEST!
		cerr << "whoops!\n";
	}
}
#endif

#ifdef _3
#include <iostream>
#include <stdexcept>
using namespace std;

struct my_exc1 : virtual exception {
	char const *what() const noexcept override { return "exc1"; }
};

struct my_exc2 : virtual exception {
	char const *what() const noexcept override { return "exc2"; }
};

struct your_exc3 : my_exc1, my_exc2 {
	char const *what() const noexcept override { return "your_exc3"; } //TEST!  
};

int main() {
	PRINT_FILE_LINE();

	try {
		throw your_exc3();
	}
	catch (exception const &e) {
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
	virtual const char *what() const noexcept {
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
	catch (const Base &e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cerr << "whoops!\n";
	}
}
#endif
