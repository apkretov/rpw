#include "stdafx.h" //#4 Ч override и final @ https://habrahabr.ru/post/182920/
#include <iostream>
using namespace std;

class B1 { //Example 1.
public:
   virtual void f(short) { cout << "B::f" << endl; }
};

class D1 : public B1 {
public:
   //Version 1. Logical error: virtual void f(int) { cout << "D3::f" << endl; }
	//Version 2. Compile-time error: virtual void f(int) override { cout << "D3::f" << endl; }
	virtual void f(short) override { cout << "D::f" << endl; } //Version 3. Correct.
};


class B2 { //Example 2.
public:
   virtual void f(int) const { cout << "B::f " << endl; }
};

class D2 : public B2 {
public:
   //Version 1. Logical error: virtual void f(int) { cout << "D3::f" << endl; }
	//Version 2. Compile-time error: virtual void f(int) override { cout << "D3::f" << endl; }
	virtual void f(int) const override { cout << "D::f" << endl; } //Version 3. Correct.
};


class B3 { //Example 3.
public:
   virtual void f(int) {std::cout << "B::f" << std::endl;}
};

class D3 : public B3
{
public:
   virtual void f(int) override final {std::cout << "D::f" << std::endl;}
};

class F3 : public D3
{
public:
   //OFF virtual void f(int) override {std::cout << "F::f" << std::endl;} //‘ункци€, объ€вленна€ как final, не может быть переопределена функцией F::f() Ч в этом случае, она переопредел€ет метод базового класса (¬) дл€ класса D.
};

int main() {
    return 0;
}

