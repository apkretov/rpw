#pragma once

#include "Command.h"
#include "DeviceStereo.h"

#pragma region MINE
class StereoOnCommand final : public Command {
	Stereo &stereo_;
public:
	explicit StereoOnCommand(Stereo &stereo) : stereo_(stereo) {}
	void execute() override { stereo_.on(); }
	void undo() override { stereo_.off(); }
};
#pragma endregion //MINE
