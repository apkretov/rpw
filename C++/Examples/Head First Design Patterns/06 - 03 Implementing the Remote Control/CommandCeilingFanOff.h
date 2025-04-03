#pragma once

#include "Command.h"
#include "DeviceCeilingFan.h"

#pragma region MINE
class CeilingFanOffCommand final : public Command {
	CeilingFan &fan_;
public:
	explicit CeilingFanOffCommand(CeilingFan &fan) : fan_(fan) {}
	void execute() override { fan_.off(); }
};
#pragma endregion //MINE
