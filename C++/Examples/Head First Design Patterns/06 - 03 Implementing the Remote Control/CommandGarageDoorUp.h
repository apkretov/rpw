#pragma once

#include "Command.h"
#include "DeviceGarageDoor.h"

#pragma region MINE
class GarageDoorUpCommand final : public Command {
	GarageDoor &garageDoor_;
public:
	explicit GarageDoorUpCommand(GarageDoor &garageDoor) : garageDoor_(garageDoor) {}
	void execute() override { garageDoor_.up(); } 
};
#pragma endregion //MINE
