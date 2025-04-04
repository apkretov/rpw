#pragma once

#include "Command.h"
#include "DeviceTV.h"

#pragma region MINE
class TVOffCommand final : public Command {
	TV &tv_;
public:
	explicit TVOffCommand(TV &tv) : tv_(tv) {}
	void execute() override { tv_.off(); }
	void undo() override { tv_.on(); }
};
#pragma endregion //MINE