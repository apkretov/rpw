#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

class base1 {
public:
	int b1 = 10;
};

class base2 {
public:
	int b2 = 20;
};

class base3 {
public:
	int b3 = 30;
};

class derived1 : public base1, public base2, public base3 {
public:
	int d = 30;
};

int main() {
	derived1 objDerived;
	cout << objDerived.b3 << endl;
	return 0;
}