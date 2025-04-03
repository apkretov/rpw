#pragma once

#include <iostream>
using std::cout;
using std::endl;

#pragma region MINE
class GarageDoor {
public:
	void up() { cout << "Garage Door is Open\n"; }
	void down() { cout << "Garage Door is Closed\n"; }
	void stop() { cout << "Garage Door is Stopped\n"; }
	void lightOn() { cout << "Garage Light is On\n"; }
	void lightOff() { cout << "Garage Light is Off\n"; }
};
#pragma endregion //MINE
