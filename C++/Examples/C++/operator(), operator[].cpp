#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

class foo {
public:
	int x;
	void operator()() { foo(); };
};

int bracketsConstructor() {
	foo* ptrFoo1 = new foo();
	foo* ptrFoo2 = new foo;
	ptrFoo1->x = 10;
	ptrFoo2->x = 20;
	cout << "ptrFoo1->x : " << ptrFoo1->x << endl;
	cout << "ptrFoo2->x : " << ptrFoo2->x << endl;
	delete ptrFoo1;
	delete ptrFoo2;
	return 0;
}

class price {
	double cdblPrice = 0;
public:
	void setPrice(double dblPrice) { cdblPrice = dblPrice; }
	double operator()() { return cdblPrice; }
};

class time {
	double cdblPrice = 0;
public:
	void setTime(double dblPrice) { cdblPrice = dblPrice; }
	double operator[](int) { return cdblPrice; }
};

void brackets() {
	price Bid;
	time Time;
	Bid.setPrice(10);
	Time.setTime(20);
	double x = Bid();
	double y = Time[0];
	cout << "Bid() = " << Bid() << endl;
	cout << "Time[0] = " << Time[0] << endl;
}

int main() {
	brackets();
	bracketsConstructor();
	return 0;
}
