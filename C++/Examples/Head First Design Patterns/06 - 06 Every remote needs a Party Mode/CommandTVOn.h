#pragma once

#include "Command.h"
#include "DeviceTV.h"

#pragma region MINE
class TVOnCommand final : public Command {
	TV &tv_;
public:
	explicit TVOnCommand(TV &tv) : tv_(tv) {}
	void execute() override { tv_.on(); }
	void undo() override { tv_.off(); }
};
#pragma endregion //MINE