#if 0

#include <cassert>
#include <iostream>
#include "../../stdafx.h"
using namespace std;

int Sum(int x, int y) {
	return x + y;
}

void TestSum() {
	assert(Sum(2, 3) == 5);
	assert(Sum(-2, -3) == -5);
	assert(Sum(-2, 0) == -2);
	assert(Sum(-2, 2) == 0);
	cout << "TestSum OK\n";
}

int main() {
	PRINT_FILE_LINE();
	TestSum();
}
#endif