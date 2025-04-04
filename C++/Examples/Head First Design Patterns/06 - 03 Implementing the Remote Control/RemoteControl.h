#pragma once

#include <array>
#include <memory>
#include <string>
#include "Command.h"
#include "CommandNo.h"
using std::array;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::to_string;

#pragma region Implementing the Remote Control
/* Java
public class RemoteControl {
	Command[] onCommands; // This time around the remote is going to handle seven On and Off commands, which we'll hold in corresponding arrays.
	Command[] offCommands;

	public RemoteControl() {
		onCommands = new Command[7]; // In the constructor all we need to do is instantiate and initialize the on and off arrays.
		offCommands = new Command[7];
		Command noCommand = new NoCommand();
		for (int i = 0; i < 7; i++) {
			onCommands[i] = noCommand;
			offCommands[i] = noCommand;
		}
	}

	public void setCommand(int slot, Command onCommand, Command offCommand) { // The setCommand() method takes a slot position and an On and Off command to be stored in that slot.It puts these commands in the on and off arrays for later use.
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}

	public void onButtonWasPushed(int slot) { onCommands[slot].execute(); } // When an On or Off button is pressed, the hardware takes care of calling the corresponding methods onButtonWasPushed() or offButtonWasPushed().
	public void offButtonWasPushed(int slot) { offCommands[slot].execute(); }

	public String toString() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------Remote Control------ - \n");
		for (int i = 0; i < onCommands.length; i++) 
			stringBuff.append("[slot " + i + "] " + onCommands[i].getClass().getName() + " " + offCommands[i].getClass().getName() + "\n");
		return stringBuff.toString(); // We've overwritten toString() to print out each slot and its corresponding command.You'll see us use this when we test the remote control.
	}
}
*/
class RemoteControl {
	static constexpr int slots = 7; // The number of slots in the remote control.
    array<shared_ptr<Command>, slots> onCommands; // This time around the remote is going to handle seven On and Off commands, which we'll hold in corresponding arrays.
    array<shared_ptr<Command>, slots> offCommands;
public:
    RemoteControl() {
        shared_ptr<Command> noCommand = make_shared<NoCommand>(); // In the constructor all we need to do is instantiate and initialize the on and off arrays.
        for (int i = 0; i < slots; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
    }

    void setCommand(int slot, shared_ptr<Command> onCommand, shared_ptr<Command> offCommand) { // The setCommand() method takes a slot position and an On and Off command to be stored in that slot.It puts these commands in the on and off arrays for later use.
        onCommands.at(slot) = onCommand;
        offCommands.at(slot) = offCommand;
    }

	void onButtonWasPushed(int slot) { onCommands[slot]->execute(); } // When an On or Off button is pressed, the hardware takes care of calling the corresponding methods onButtonWasPushed() or offButtonWasPushed().
    void offButtonWasPushed(int slot) { offCommands[slot]->execute(); }

    string toString() const { // We've overwritten toString() to print out each slot and its corresponding command.You'll see us use this when we test the remote control.
        string result = "\n------Remote Control------ - \n";
        for (int i = 0; i < slots; i++)
            result += "[slot " + to_string(i) + "] " + typeid(*onCommands[i]).name() + " " + typeid(*offCommands[i]).name() + "\n";
        return result; 
    }
};
#pragma endregion //Implementing the Remote Control
