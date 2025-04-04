#pragma once

#include <iostream>
#include <string>
#include <string_view>
using std::cout;
using std::string;
using std::string_view;

#pragma region MINE
class CeilingFan {
	string location_;
public:
	explicit CeilingFan(string_view location) : location_(location) {}
	void on() { cout << location_ << " CeilingFan is On\n"; }
	void off() { cout << location_ << " CeilingFan is Off\n"; }
};
#pragma endregion //MINE
