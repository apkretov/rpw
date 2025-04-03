#pragma once

#include "Command.h"
#include "DeviceCeilingFan.h"

#pragma region MINE
class CeilingFanOnCommand final : public Command {
	CeilingFan &fan_;
public:
	explicit CeilingFanOnCommand(CeilingFan &fan) : fan_(fan) {}
	void execute() override { fan_.on(); } 
};
#pragma endregion //MINE
