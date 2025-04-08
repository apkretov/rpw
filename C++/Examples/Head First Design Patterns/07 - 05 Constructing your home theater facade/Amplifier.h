#pragma once
#include <string>
class DvdPlayer;

#pragma region MINE
class Amplifier {
public:
	void on() {}
	void off() {}
	void setDvd(DvdPlayer &dvd) {}
	void setSurroundSound() {}
	void setVolume(int level) {}
};
#pragma endregion //MINE
