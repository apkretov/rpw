#pragma once

#pragma region Perplexity: The original exception object at the throw site will typically be destroyed as control leaves the throw block.

#include <iostream>
#include <stdexcept>
using namespace std;

#undef ORIG
#define MINE

#ifdef ORIG
class MyException {
public:
	MyException() { cout << "Constructor\n"; }
	~MyException() { cout << "Destructor\n"; }
	MyException(const MyException&) { cout << "Copy Constructor\n"; }
};

void test() {
	try {
		MyException ex;
		cout << "Throwing\n";
		throw ex;  // Exception object copied here
		cout << "After throw\n";  // Not executed
	}
	catch (MyException& e) {
		cout << "Caught\n";
	}
}
#endif // ORIG

#ifdef MINE
class MyException {
public:
	MyException() { cout << "Constructor"; printThis(); }
	MyException(const MyException&) { cout << "Copy Constructor"; printThis(); }
	MyException(MyException&&) noexcept { cout << "Move Constructor"; printThis(); }
	~MyException() { cout << "Destructor"; printThis(); }
private:
	void printThis() { cout << ' ' << this << '\n'; }
};

void test() {
	try {
		MyException ex;
		cout << "Throwing\n";
		throw ex;  // Exception object copied here
		cout << "After throw\n";  // Not executed
	}
	catch (MyException& e) {
		cout << "Caught\n";
	}
}
#endif // MINE

int main_01() {
	test();
	return 0;
}
#pragma endregion //Perplexity: The original exception object at the throw site will typically be destroyed as control leaves the throw block.
