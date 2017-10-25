#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

extern const int x;

void doSomething() {
	//x = 20; //ERROR!
	cout << "doSomething: x = " << x << endl;
}
