#pragma once

#include <iostream>
using std::cout;

#pragma region MINE
class Stereo {
	string location_;
public:
	explicit Stereo(string_view location) : location_(location) {}
	void on() { cout << location_ << " Stereo is On\n"; }
	void off() { cout << location_ << " Stereo is Off\n"; }
	void setCD() { cout << location_ << " Stereo CD is Set\n"; }
	void setDVD() { cout << location_ << " Stereo DVD is Set\n"; }
	void setRadio() { cout << location_ << " Stereo Radio is Set\n"; }
	void setVolume(int volume) { cout << location_ << " Stereo Volume is Set to " + volume + '\n'; }
};
#pragma endregion //MINE
