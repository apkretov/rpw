#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

class test {
public:
	static void fnc() {cout << "Hello, World!" << endl; }
};

int main() {
	test::fnc();
	return 0;
}

