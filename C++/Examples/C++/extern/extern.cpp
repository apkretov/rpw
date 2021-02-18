// Test.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

extern const int x(10);
extern void doSomething();

int main() {
	cout << "main: x = " << x << endl;
	doSomething();
	return 0;
}

