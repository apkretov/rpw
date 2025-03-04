#include "stdafx.h" //dynamic_cast conversion @ http://en.cppreference.com/w/cpp/language/dynamic_cast
#include <iostream>
using namespace std;

struct V {
	virtual void f() {};  // must be polymorphic to use runtime-checked dynamic_cast
};

struct A : virtual V {};

struct B : virtual V {
	B(V* v, A* a) { // casts during construction (see the call in the constructor of D below)
		dynamic_cast<B*>(v); // well-defined: v of type V*, V is the base of B, results in B*
		dynamic_cast<B*>(a); // undefined behavior: a has type A*, A is not a base of B
}	};

struct D : A, B {
	D() : B((A*)this, this) {}
};

struct Base {
	virtual ~Base() {}
};

struct Derived : Base {
	virtual void name() {}
};

int main() {
	D d; // the most derived object
	A& a = d; // upcast, dynamic_cast may be used, but unnecessary
	D& new_d = dynamic_cast<D&>(a); // downcast
	B& new_b = dynamic_cast<B&>(a); // sidecast

	Base* b1 = new Base;
	if (Derived* d = dynamic_cast<Derived*>(b1))	{
		cout << "downcast from b1 to d successful\n";
		d->name(); // safe to call
	}

	Base* b2 = new Derived;
	if (Derived* d = dynamic_cast<Derived*>(b2))	{
		cout << "downcast from b2 to d successful\n";
		d->name(); // safe to call
	}

	delete b1;
	delete b2;
}