#pragma once

#include "Command.h"
#include "CeilingFan.h"

#pragma region MINE
class LightOnCommand final : public Command {
	CeilingFan &fan_;
public:
	explicit LightOnCommand(CeilingFan &fan) : fan_(fan) {} 
	void execute() override { fan_.on(); } 
};
#pragma endregion //MINE
