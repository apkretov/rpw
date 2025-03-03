#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region you.com
struct Base {
	Base() {}
};

struct Derived : public Base {
	Derived() {}
};

void mine() {
	try {
		throw Derived();
	}
	catch (const Base &base) {
		cerr << "caught Base\n";
	}
	catch (const Derived &derived) {
		cerr << "caught Derived\n";
	}
}
#pragma endregion

int main() {
	print_file_line();

	mine();

	return 0;
}
#endif

#ifdef EX_18_01

#include <iostream>
#include <stdexcept>
#include "../../stdafx.h"
using namespace std;

#pragma region you.com
int calculateFactorial(int n) {
	if (n < 0)
		throw range_error("Factorial is not defined for negative numbers");

	int result = 1;
	for (int i = 1; i <= n; ++i) {
		if (result > INT_MAX / i) // Check for potential overflow
			throw range_error("Factorial result is out of range for integer type");
		result *= i;
		cout << "result = " << result << endl;
	}
	return result;
}

void main_you_com() {
	try {
		int number = 15;  // Example input
		int factorial = calculateFactorial(number);
		cout << "Factorial of " << number << " is: " << factorial << endl;
	}
	catch (const range_error &e) {
		cerr << "Range error caught: " << e.what() << endl;
	}
	catch (const exception &e) {
		cerr << "Exception caught: " << e.what() << endl;
	}
}
#pragma endregion

[[noreturn]] void a() {
	cout << "a()\n";
	range_error r("error"); // (a)
	throw r;
}

[[noreturn]] void b() {
	cout << "b()\n";
	range_error r("error");
	exception *p = &r; // (b)
#ifdef _1
	throw *p;
#else // _2
	throw p; //TEST!! //																																			If a throw expression dereferences a pointer to a base - class type, and that pointer points to a derived - type object, then the thrown object is sliced down(§ 15.2.3, p. 603); only the base - class part is thrown
#endif
}

void ex() {
	try {
		a();
	}
	catch (const range_error &r) {
		cerr << "caught range_error &r: " << r.what() << '\n';
	}
	catch (const exception &e) {
		cerr << "caught exception &e: " << e.what() << '\n';
	}

	try {
		b();
	}
	catch (range_error *p) {
		cerr << "caught range_error *p: " << p->what() << '\n';
	}
	catch (exception &p) {
		cerr << "caught exception &p: " << p.what() << '\n';
	}
	catch (exception *p) {
		cerr << "caught exception *p: " << p->what() << '\n';
	}
}

int main() {
	print_file_line();

	//main_you_com();
	ex();

	return 0;
}
#endif

#ifdef EX_18_02

#include <iostream>
#include "vld.h"
#include "../../stdafx.h"
using namespace std;

void exercise(int *b, int *e) {
	vector<int> v(b, e);
	int *p = new int[v.size()];
	ifstream in("ints");
	throw exception("exception occurs here"); // exception occurs here
	delete[]p; //MINE
}

int main() {
	print_file_line();

	try {
		exercise(nullptr, nullptr);
	}
	catch (const exception &e) {
		cerr << "Exception: " << e.what() << '\n';
	}

	return 0;
}
#endif

#ifdef EX_18_03

#include <iostream>
#include <memory>
#include "vld.h"
#include "../../stdafx.h"
using namespace std;

[[noreturn]] void exercise_1(int *b, int *e) {
	vector<int> v(b, e);
	auto sp = make_shared<vector<int>>(v.size());
	ifstream in("ints");
	throw exception("exception occurs here"); // exception occurs here
}

void exercise_2_BAD(int *b, int *e) {
	vector<int> v(b, e);
	int *p = new int[v.size()];
	try {
		ifstream in("ints");
		throw exception("exception occurs here"); // exception occurs here
		delete[]p;

	}
	catch (const exception &e1) {
		cerr << log_str(e1.what())  << '\n';
		try {
			delete[]p;
		}
		catch (const exception &e2) {
			cerr << log_str(e2.what()) << '\n';
		}
	}
}

class Array {
	int *p;
public:
	explicit Array(size_t n) : p(new int[n]) {}
	Array(const Array &a) = delete;
	Array &operator=(const Array &a) = delete;
	~Array() { delete[]p; }
};

[[noreturn]] void exercise_3(int *b, int *e) {
	vector<int> v(b, e);
	Array arr(v.size());
	ifstream in("ints");
	throw exception("exception occurs here"); // exception occurs here
}

int main() {
	print_file_line();

	try {
		exercise_1(nullptr, nullptr);
	}
	catch (const exception &e) {
		cerr << log_str(e.what()) << '\n';
	}

	try {
		exercise_2_BAD(nullptr, nullptr);
	}
	catch (const std::exception &e) {
		cerr << log_str(e.what()) << '\n';
	}

	try {
		exercise_3(nullptr, nullptr);
	}
	catch (const exception &e) {
		cerr << log_str(e.what()) << '\n';
	}

	return 0;
}
#endif
