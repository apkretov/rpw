#pragma once

#ifndef EX_14_50

#include <iostream>

struct LongDouble {
	LongDouble(double d = 0.0) : val(d) {
		std::cout << "Constructor\n";
	}

	double val;

	operator double() {
		std::cout << "operator double()\n";
		return val;
	}

	operator float() {
		std::cout << "operator float()\n";
		return static_cast<float>(val);
	}
};
#endif