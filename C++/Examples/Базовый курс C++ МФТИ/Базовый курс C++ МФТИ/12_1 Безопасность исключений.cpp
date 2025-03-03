#include <iostream>
#include "stdafx.h"
#include <type_traits>
using namespace std;

#ifdef PERPLEXITY // An example of using is_fundamental_v
int main() {
	PRINT_FILE_LINE();

	cout << boolalpha;
	cout << "is_fundamental_v<int>: " << is_fundamental_v<int> << '\n'; //TEST!
	cout << "is_fundamental_v<float&>: " << is_fundamental_v<float &> << '\n';
	cout << "is_fundamental_v<double*>: " << is_fundamental_v<double *> << '\n';
	cout << "is_fundamental_v<string>: " << is_fundamental_v<string> << '\n';
	cout << "is_fundamental_v<void>: " << is_fundamental_v<void> << '\n';
	return 0;
}
#endif

#ifdef _1
#include <cassert>

struct ThrowingCtor { 
	ThrowingCtor() {} 
};

void foo(ThrowingCtor) noexcept;
void foo(int) noexcept;

int main() {
	PRINT_FILE_LINE();

	assert(noexcept(foo(1)) == true);
	assert(noexcept(foo(ThrowingCtor{})) == false); //TEST!

	return 0;
}
#endif

#ifdef _2 // 08-exceptions/noexc.cc @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/noexc.cc
struct DefaultCtor {};

struct ThrowingCtor {
#ifndef ORIG
	ThrowingCtor() {}; //TEST! //																														=default will create noexcept one
#else //MINE
	ThrowingCtor() = default;
#endif
	ThrowingCtor(const ThrowingCtor &) = default;
	ThrowingCtor(ThrowingCtor &&) = default;
};

struct Inherited {
	ThrowingCtor c;
};

void foo(int) noexcept;
void foo(DefaultCtor) noexcept;
void foo(ThrowingCtor) noexcept;

int main() {
	PRINT_FILE_LINE();

	cout << boolalpha;
	cout << "noexcept(null pointer deref): " << noexcept(*static_cast<int *>(nullptr)) << '\n'; //TEST!

	cout << "foo(int): " << noexcept(foo(1)) << '\n';
	cout << "foo(Default): " << noexcept(foo(DefaultCtor{})) << '\n';
	cout << "foo(Throwing): " << noexcept(foo(ThrowingCtor{})) << '\n';

	cout << "Default constr: " << is_nothrow_constructible_v<DefaultCtor> << '\n'; //TEST!
	cout << "Default copy constr: "	<< is_nothrow_copy_constructible_v<DefaultCtor> << '\n';
	cout << "Default move constr: "	<< is_nothrow_move_constructible_v<DefaultCtor> << '\n';

	cout << "Inherited constr: " << is_nothrow_constructible_v<Inherited> << '\n'; //TEST!
	cout << "Inherited copy constr: " << is_nothrow_copy_constructible_v<Inherited> << '\n';
	cout << "Inherited move constr: " << is_nothrow_move_constructible_v<Inherited> << '\n';

#ifndef MINE
	cout << '\n';
	cout << "is_nothrow_constructible_v<ThrowingCtor>: " << is_nothrow_constructible_v<ThrowingCtor> << '\n'; //TEST!
	cout << "noexcept(ThrowingCtor::ThrowingCtor()): " << noexcept(ThrowingCtor::ThrowingCtor()) << '\n';
	cout << "noexcept(Inherited::Inherited()): " << noexcept(Inherited::Inherited()) << '\n';
#endif
}
#endif

#ifdef _3 // 08-exceptions/noexc-dtor.cc @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/noexc-dtor.cc
#include <stdexcept>

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
	catch (runtime_error &e) {
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
	catch (runtime_error &e) {
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
		catch (const runtime_error &e) {
			cerr << "My exception caught\n";
		}
#endif
	}
	catch (runtime_error &e) {
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
#endif

#ifdef _4 // 08-exceptions/opnew-cst.cc @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/opnew-cst.cc

#include <cstdlib>
#include <list>

void *operator new(size_t n) {
	void *p = malloc(n);
	if (!p)
		throw bad_alloc{};
	printf("Alloc: %p, size is %zu\n", p, n);
	return p;
}

void operator delete(void *mem) noexcept {
	printf("Free: %p\n", mem);
	free(mem);
}

struct Widget {
	static void *operator new(size_t n); //TEST! //																												C++.Primer.5th.Edition_2013.pdf: implicitly static, p. 821.
	static void operator delete(void *mem) noexcept; //TEST! //																									C++.Primer.5th.Edition_2013.pdf: implicitly static, p. 821.
	int n[4];
};

void *Widget::operator new(size_t n) {
	void *p = malloc(n);
	if (!p)
		throw bad_alloc{};
	printf("Custom alloc: %p, size is %zu\n", p, n);
	return p;
}

void Widget::operator delete(void *mem) noexcept {
	printf("Custom free: %p\n", mem);
	free(mem);
}

int main() {
	PRINT_FILE_LINE();

	list<int> l;
	l.push_back(42);
	Widget *w = new Widget;
	delete w;
}
#endif
