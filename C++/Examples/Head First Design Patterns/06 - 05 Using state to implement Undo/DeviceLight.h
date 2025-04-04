#pragma once

#include <iostream>
#include <string>
#include <string_view>
using std::cout;
using std::string;
using std::string_view;

#pragma region MINE
class Light {
	string location_;
public:
	explicit Light(string_view location) : location_(location) {}
	void on() { cout << location_ << " Light is On\n"; }
	void off() { cout << location_ << " Light is Off\n"; }
};
#pragma endregion //MINE
