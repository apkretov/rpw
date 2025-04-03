#pragma once

#include <iostream>
#include <string>
#include <string_view>
using std::cout;
using std::string;
using std::string_view;

#pragma region MINE
class Light {
	string name_;
public:
	explicit Light(string_view name) : name_(name) {}
	void on() { cout << "Light is On\n"; }
	void off() { cout << "Light is Off\n"; }
};
#pragma endregion //MINE
