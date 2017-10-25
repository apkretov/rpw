#include "stdafx.h" //Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c
#include <iostream>
using namespace std;

int globalvar = 20;

int& foo() { return globalvar; }

int main() {
	cout << globalvar << endl;
	foo() = 10;
	cout << globalvar << endl;
	return 0;
}