#pragma once

#include "Command.h"
#include "DeviceCeilingFan.h"

#pragma region MINE
class CeilingFanOffCommand final : public Command {
	CeilingFan &ceilingFan_;
public:
	explicit CeilingFanOffCommand(CeilingFan &ceilingFan) : ceilingFan_(ceilingFan) {}
	void execute() override { ceilingFan_.off(); }
	void undo() override { ceilingFan_.medium(); }
};
#pragma endregion //MINE
