#include "stdafx.h"
#include <iostream>
#include <new>
using namespace std;

int main() {
	cout << "Start the endless loop with new(nothrow) auto(1e30)..." << endl;
	while (new(nothrow) auto(1e30) != nullptr) { }
	cout << "The loop terminated on new(nothrow) auto(1e30) != nullptr" << endl;
	return 0;
}
