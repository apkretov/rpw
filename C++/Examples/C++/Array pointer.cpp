#include "stdafx.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main() {
	int a[] = {0, 1, 2, 3, 4, 5 };
	cout << "a[5] = " << a[5] << endl;
	cout << "*a = " << *a << endl;
	int* b = a + 5;
	cout << "*b = " << *b << endl;
	cout << "*(a + 5) = " << *(a + 5) << endl;
	cout << "*--b = " << *--b << endl;
	char* c = "char c";
	cout << "*(c + 5) = " << *(c + 5) << endl;
	return 0;
}
