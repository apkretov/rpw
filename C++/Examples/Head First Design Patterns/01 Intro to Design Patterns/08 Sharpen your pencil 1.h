#pragma once

#include <iostream>
using std::cout;

struct FlyRocketPowered : FlyBehavior {
	void fly() const override { cout << "I’m flying with a rocket!\n"; }
};
