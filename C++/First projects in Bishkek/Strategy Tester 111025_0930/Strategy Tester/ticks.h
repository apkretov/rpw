#ifndef TICKS_H
#define TICKS_H
#pragma once
#include "Account.h"

class ticks {
	double Price;
	void EnterPrice(); //enter a Price
public:
	explicit ticks(double);
	void Generate(account&, double&, double&, void(*)()); // Generate a tick
};
#endif