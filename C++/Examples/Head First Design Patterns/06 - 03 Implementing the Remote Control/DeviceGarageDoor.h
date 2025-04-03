#pragma once

#include <iostream>
#include <string>
using std::cout;
using std::string;

#pragma region MINE
class GarageDoor {
	string name_;
public:
	explicit GarageDoor(string_view name) : name_(name) {}
	void up() { cout << name_ << " Garage Door is Open\n"; }
	void down() { cout << name_ << " Garage Door is Closed\n"; }
	void stop() { cout << name_ << " Garage Door is Stopped\n"; }
	void lightOn() { cout << name_ << " Garage Light is On\n"; }
	void lightOff() { cout << name_ << " Garage Light is Off\n"; }
};
#pragma endregion //MINE
