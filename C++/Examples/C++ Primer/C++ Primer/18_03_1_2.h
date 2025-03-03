#pragma once

#ifndef EX_18_22

#include <iostream>
using std::cout;

struct A {
	A() { cout << "A\n"; }
};

struct B : public A {
	B() { cout << "B\n"; }
};

struct C : public B {
	C() { cout << "C\n"; }
};

struct X {
	X() { cout << "X\n"; }
};

struct Y {
	Y() { cout << "Y\n"; }
};

struct Z : public X, public Y {
	Z() { cout << "Z\n"; }
};

struct MI : public C, public Z {
	MI() { cout << "MI\n"; }
};
#endif