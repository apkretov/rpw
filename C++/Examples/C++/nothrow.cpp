#include "stdafx.h"
#include <iostream>
#include <new>
using namespace std;

int main() {
	cout << "Start the endless loop with new(nothrow) auto(10000000000000000000)..." << endl;
	while (new(nothrow) auto(10000000000000000000) != nullptr) { }
	cout << "The loop terminated on new(nothrow) int(10000) != nullptr" << endl;
	return 0;
}

