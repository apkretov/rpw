#pragma once

#include "Command.h"
#include "DeviceHottub.h"

#pragma region MINE
class HottubOffCommand final : public Command {
	Hottub &hottub_;
public:
	explicit HottubOffCommand(Hottub &hottub) : hottub_(hottub) {}
	void execute() override { hottub_.off(); }
	void undo() override { hottub_.on(); }
};
#pragma endregion //MINE