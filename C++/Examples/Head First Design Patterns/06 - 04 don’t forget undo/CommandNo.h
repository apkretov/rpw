#pragma once

#include "Command.h"

#pragma region MINE
class NoCommand final : public Command {
public:
	void execute() override { /*No action*/}
	void undo() override { /*No action*/ }
};
#pragma endregion //MINE
