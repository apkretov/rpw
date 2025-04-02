#pragma once

#include <iostream>
using namespace std;

#pragma region MINE
class Light {
public:
	void on() { cout << "Light::on();\n"; }
};
#pragma endregion //MINE
