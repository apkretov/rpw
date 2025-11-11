#pragma once

#include <stdexcept> // 08-exceptions/noexc-dtor.cc @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/noexc-dtor.cc

//MINE #define BAD 
#ifdef BAD
struct T {
	~T() {
		cerr << "Dtor threw an exception...\n"; //MINE
		throw runtime_error("");
	}
};

void test0() {
	try {
		T t;
		cout << "Ending test0()...\n"; //MINE
	}
	catch (runtime_error& e) {
		cerr << "Exception caught\n";
	}
	cout << "Success\n";
}
#endif

struct S {
	~S() noexcept(false) { //TEST
		if (uncaught_exceptions()) //TEST!
			cerr << "Dtor called in unwinding\n";
		throw runtime_error("");
	}
};

void test1() {
	try {
		S s;
	}
	catch (runtime_error& e) {
		cerr << "Exception caught\n";
	}
	cerr << "Success\n";
}

void test2() {
	try {
		S s;
#ifndef ORIG
		throw runtime_error("");
#else //MINE
		try {
			throw runtime_error("");
		}
		catch (const runtime_error& e) {
			cerr << "My exception caught\n";
		}
#endif
	}
	catch (runtime_error& e) {
		cerr << "Exception caught\n";
	}
	cerr << "Success\n";
}

int main() {
	PRINT_FILE_LINE();

#ifdef BAD
	cerr << "test0: ";
	test0();
#endif
	cerr << "test1: ";
	test1();
	cerr << "test2: ";
	test2();
}