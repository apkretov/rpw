#pragma once

#include <iostream>
#include <string>
using std::cout;
using std::string;

#pragma region MINE
class GarageDoor {
	string location_;
public:
	explicit GarageDoor(string_view location) : location_(location) {}
	void up() { cout << location_ << " Garage Door is Open\n"; }
	void down() { cout << location_ << " Garage Door is Closed\n"; }
	void stop() { cout << location_ << " Garage Door is Stopped\n"; }
	void lightOn() { cout << location_ << " Garage Light is On\n"; }
	void lightOff() { cout << location_ << " Garage Light is Off\n"; }
};
#pragma endregion //MINE
