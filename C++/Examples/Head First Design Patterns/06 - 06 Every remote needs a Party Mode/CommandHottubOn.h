#pragma once

#include "Command.h"
#include "DeviceHottub.h"

#pragma region MINE
class HottubOnCommand final : public Command {
	Hottub &hottub_;
public:
	explicit HottubOnCommand(Hottub &hottub) : hottub_(hottub) {}
	void execute() override { hottub_.on(); }
	void undo() override { hottub_.off(); }
};
#pragma endregion //MINE