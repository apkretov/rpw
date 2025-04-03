#pragma once

#include "Command.h"
#include "GarageDoor.h"

#pragma region MINE
class GarageDoorOpenCommand final : public Command { // This is a command, so we need to implement the Command interface.
	GarageDoor &garageDoor_;
public:
	explicit GarageDoorOpenCommand(GarageDoor &garageDoor) : garageDoor_(garageDoor) {} // The constructor is passed the specific garage door that this command is going to control.
	void execute() override { garageDoor_.up(); } // The execute method calls the up() method on the receiving object, which is the garage door we are controlling.
};
#pragma endregion //MINE
