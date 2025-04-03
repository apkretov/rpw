#pragma once

#include <iostream>
using namespace std;

#pragma region MINE
class Light {
public:
	void on() { cout << "Light is On\n"; }
	void off() { cout << "Light is Off\n"; }
};
#pragma endregion //MINE
