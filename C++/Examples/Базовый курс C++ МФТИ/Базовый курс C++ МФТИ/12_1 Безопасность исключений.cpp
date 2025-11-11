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

#ifdef _2 
#include "12 noexc.cc.h"
#endif

#ifdef _3 
#include "12 noexc-dtor.cc.h"
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
