#pragma once

#include <iostream>
using std::cout;

#pragma region MINE
class Stereo {
	string name_;
public:
	explicit Stereo(string_view name) : name_(name) {}
	void on() { cout << name_ << " Stereo is On\n"; }
	void off() { cout << name_ << " Stereo is Off\n"; }
	void setCD() { cout << name_ << " Stereo CD is Set\n"; }
	void setDVD() { cout << name_ << " Stereo DVD is Set\n"; }
	void setRadio() { cout << name_ << " Stereo Radio is Set\n"; }
	void setVolume(size_t volume) { cout << name_ << " Stereo Volume is Set to " + volume + '\n'; }
};
#pragma endregion //MINE
