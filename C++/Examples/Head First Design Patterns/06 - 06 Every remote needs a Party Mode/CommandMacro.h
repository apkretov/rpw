#pragma once

#include <memory>
#include <vector>
#include "Command.h"
using std::shared_ptr;
using std::vector;

#pragma region Every remote needs a Party Mode!
/* Java
public class MacroCommand implements Command { // Mary's idea is to make a new kind of Command that can execute other Commands... and more than one of them! Pretty good idea, huh ?
	Command[] commands;
	public MacroCommand(Command[] commands) { this.commands = commands; } // Take an array of Commands and store them in the MacroCommand.

	public void execute() {
		for (int i = 0; i < commands.length; i++)
			commands[i].execute(); // When the macro gets executed by the remote, execute those commands one at a time.
	}
}
*/
class MacroCommand final : public Command { // Mary's idea is to make a new kind of Command that can execute other Commands... and more than one of them! Pretty good idea, huh ?
    vector<shared_ptr<Command>> commands_;
public:
    explicit MacroCommand(vector<shared_ptr<Command>> commands) : commands_(std::move(commands)) {} // Take an array of Commands and store them in the MacroCommand.

    void execute() override {
        for (const auto& command : commands_)
            command->execute(); // When the macro gets executed by the remote, execute those commands one at a time.
    }

#pragma region Exercise
	void undo() override {
		for (const auto &command : commands_)
			command->undo();
	}
#pragma endregion //Exercise
};
#pragma endregion //Every remote needs a Party Mode!
