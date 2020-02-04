#include "stdafx.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

int main() {
	int a = 1, b = 2;
	cout << "assert(a == 1)...\n";
	assert(a == 1);
	cout << "Asserted!\n\n";
	cout << "assert(a == b)...\n";
	assert(a == b);
	cout << "\nFinish.";
	return 0;
}
