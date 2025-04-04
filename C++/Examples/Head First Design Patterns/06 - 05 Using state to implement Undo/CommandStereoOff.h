#pragma once

#include "Command.h"
#include "DeviceStereo.h"

#pragma region MINE
class StereoOffCommand final : public Command {
	Stereo &stereo_;
public:
	explicit StereoOffCommand(Stereo &stereo) : stereo_(stereo) {} 
	void execute() override { stereo_.off(); }
};
#pragma endregion //MINE
