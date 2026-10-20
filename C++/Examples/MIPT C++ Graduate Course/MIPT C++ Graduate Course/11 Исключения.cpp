#include <iostream>
#include <stdexcept>
#include "../../stdafx.h"
using namespace std;

#if 0 //Порождение ошибки
struct UnwShow {
	UnwShow() { std::cout << "ctor\n"; }
	~UnwShow() { std::cout << "dtor\n"; }
};
int foo(int n) {
	UnwShow s;
	if (n == 0) abort(); // abort это убийство
	foo(n - 1);
}

int main() {
	PRINT_FILE_LINE();
	foo(4); // что на экране?  
}
#endif

#if 0 // Порождение исключения
struct UnwShow {
	UnwShow() { std::cout << "ctor\n"; }
	~UnwShow() { std::cout << "dtor\n"; }
};

int foo(int n) {
	UnwShow s;
	if (n == 0) 
		throw 1;
	foo(n - 1);
}

int main() {
	try { // вызов внутри try-блока
		foo(4); // что на экране?
	}
	catch (const int) {
		cerr << "Error caught" << '\n';
	}
}
#endif

#if 0
#include "11 throws_cc.h"
#endif

#if 0
struct Base {
	Base() { cout << "Base " << format_this(this) << '\n'; } //MINE
	Base(const Base&) { cout << "Base Copy " << format_this(this) << '\n'; } //MINE
	Base(Base&&) noexcept { cout << "Base Copy " << format_this(this) << '\n'; }  //MINE
	virtual ~Base() { cout << "~Base() " << format_this(this) << '\n'; }
};

struct Derived : Base {
	Derived() { cout << "Derived " << format_this(this) << '\n'; } //MINE
	Derived(const Derived&) { cout << "Derived Copy " << format_this(this) << '\n'; } //MINE
	Derived(Derived&&) noexcept { cout << "Derived Copy " << format_this(this) << '\n'; } //MINE
	virtual ~Derived() { cout << "~Derived() " << format_this(this) << '\n'; }
};

int main() {
	PRINT_FILE_LINE();

	try {
		throw Derived();
	}
#if defined(CORR)
	catch (Base& b) {
		cout << "catch (Base& b):\n";
	}
#endif
	catch (Base b) { //TEST!
		cout << "catch (Base):\n";
	}
	catch (Derived d) {
		cout << "catch (Derived):\n";
	}
}
#endif

#if 0
#include "11 multinh_cc.h"
#endif
