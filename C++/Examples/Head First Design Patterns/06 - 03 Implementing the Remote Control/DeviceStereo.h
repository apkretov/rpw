#pragma once

#include <iostream>
using std::cout;

#pragma region MINE
class Stereo {
	string name_;
public:
	explicit Stereo(string_view name) : name_(name) {}
	void on() { cout << "Stereo is On\n"; }
	void off() { cout << "Stereo is Off\n"; }
	void setCD() { cout << "Stereo CD is Set\n"; }
	void setDVD() { cout << "Stereo DVD is Set\n"; }
	void setRadio() { cout << "Stereo Radio is Set\n"; }
	void setVolume(size_t volume) { cout << "Stereo Volume is Set to " + volume + '\n'; }
};
#pragma endregion //MINE
