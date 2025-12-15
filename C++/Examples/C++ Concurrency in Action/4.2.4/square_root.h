#pragma once

#include <stdexcept>
#include <cmath>

double square_root(double x) {
	if (x < 0) {
		throw std::out_of_range("x<0");
	}
	return sqrt(x);
}
