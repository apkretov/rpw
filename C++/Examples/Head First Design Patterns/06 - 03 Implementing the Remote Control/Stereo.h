#pragma once

#include <iostream>
using namespace std;

#pragma region MINE
class Stereo {
public:
	void on() { cout << "Stereo is On\n"; }
	void off() { cout << "Stereo is Off\n"; }
	void setCd() { cout << "Stereo CD is Set\n"; }
	void setDvd() { cout << "Stereo DVD is Set\n"; }
	void setRadio() { cout << "Stereo Radio is Set\n"; }
	void setVolume() { cout << "Stereo Volume is Set\n"; }
};
#pragma endregion //MINE
