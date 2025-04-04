#pragma once

#include "Command.h"
#include "DeviceGarageDoor.h"

#pragma region MINE
class GarageDoorDownCommand final : public Command {
	GarageDoor &garageDoor_;
public:
	explicit GarageDoorDownCommand(GarageDoor &garageDoor) : garageDoor_(garageDoor) {}
	void execute() override { garageDoor_.down(); }
};
#pragma endregion //MINE
