#include "stdafx.h" //Understanding lvalues and rvalues in C and C++ @ http://eli.thegreenplace.net/2011/12/15/understanding-lvalues-and-rvalues-in-c-and-c
#include <iostream>
using namespace std;

int main() {
	int arr[] = { 1, 2 };
	cout << arr[1] << endl;
	int* p = &arr[0];
	*(p + 1) = 10;   // OK: p + 1 is an rvalue, but *(p + 1) is an lvalue
	cout << arr[1] << endl;
	return 0;
}

