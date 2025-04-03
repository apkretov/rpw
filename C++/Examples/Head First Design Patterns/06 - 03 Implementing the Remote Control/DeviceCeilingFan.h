#pragma once

#include <iostream>
#include <string>
#include <string_view>
using std::cout;
using std::string;
using std::string_view;

#pragma region MINE
class CeilingFan {
	string name_;
public:
	explicit CeilingFan(string_view name) : name_(name) {}
	void on() { cout << name_ << " CeilingFan is On\n"; }
	void off() { cout << name_ << " CeilingFan is Off\n"; }
};
#pragma endregion //MINE
