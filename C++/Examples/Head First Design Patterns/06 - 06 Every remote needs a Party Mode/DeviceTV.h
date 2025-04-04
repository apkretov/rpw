#pragma once

#include <iostream>
#include <string>
#include <string_view>
using std::cout;
using std::string;
using std::string_view;

#pragma region MINE
class TV {
	string location_;
public:
	explicit TV(string_view location) : location_(location) {}
	void on() { cout << location_ << " TV is On\n"; }
	void off() { cout << location_ << " TV is Off\n"; }
};
#pragma endregion //MINE
