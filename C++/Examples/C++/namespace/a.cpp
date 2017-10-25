#include "stdafx.h"
#include "constants.h"

double x = Constants::my_gravity;

void foo () {
	double x = Constants::my_gravity;
	double y = Constants::pi;
	double z = Constants::sum(10, 20);
	z = Functions::sum_(100, 200);
}