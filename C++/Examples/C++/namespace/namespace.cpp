#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;
#include "constants.h"

extern void foo();

int main() {
	double radius = 2;
	double circumference = 2 * radius * Constants::pi;
	cout << "circumference = " << circumference << endl;
	cout << "Constants::sum(2, 5) = " << Constants::sum(2, 5) << endl;
	foo();
	cout << "Functions::sum_(20, 50) = " << Functions::sum_(20, 50) << endl;
   return 0;
}

