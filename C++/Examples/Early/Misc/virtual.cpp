#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

class base {
public:
	virtual void fnc(){ cout << "Base" << endl; }
};

class derived : public base {
public:
	/*Optional: virtual*/ void fnc() { cout << "Derived" << endl; }
};

int main() {
	derived objDerived;
	base* ptrBase;
	ptrBase = &objDerived;
	ptrBase->fnc();
	return 0;
}

