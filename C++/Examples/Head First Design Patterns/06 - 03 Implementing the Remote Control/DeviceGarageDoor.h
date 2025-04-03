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
	void up() { cout << "Garage Door is Open\n"; }
	void down() { cout << "Garage Door is Closed\n"; }
	void stop() { cout << "Garage Door is Stopped\n"; }
	void lightOn() { cout << "Garage Light is On\n"; }
	void lightOff() { cout << "Garage Light is Off\n"; }
};
#pragma endregion //MINE
