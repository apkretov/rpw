#include "stdafx.h"

namespace Constants { // actual global variables
	extern const double pi(3.14159);
	extern const double avogadro(6.0221413e23);
	extern const double my_gravity(9.2); // m/s^2 -- gravity is light on this planet
	double sum(double a, double b) {
		return a + b;
	}
}

namespace Functions {
	double sum_(double a, double b) {
		return a + b;
	}
}