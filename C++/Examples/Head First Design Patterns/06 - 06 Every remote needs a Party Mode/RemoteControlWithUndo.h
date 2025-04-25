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

#pragma region To add support for the undo button
/* Java
public class RemoteControlWithUndo {
	Command[] onCommands; 
	Command[] offCommands;
	Command undoCommand; // This is where we'll stash the last command executed for the undo button.

	public RemoteControlWithUndo() {
		onCommands = new Command[7]; 
		offCommands = new Command[7];
		Command noCommand = new NoCommand();
		for (int i = 0; i < 7; i++) {
			onCommands[i] = noCommand;
			offCommands[i] = noCommand;
		}
		undoCommand = noCommand; // Just like the other slots, undo starts off with a NoCommand, so pressing undo before any other button won't do anything at all.
	}

	public void setCommand(int slot, Command onCommand, Command offCommand) { 
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}

	public void onButtonWasPushed(int slot) { 
		onCommands[slot].execute(); 
		undoCommand = onCommands[slot]; // When a button is pressed, we take the command and first execute it; then we save a reference to it in the undoCommand instance variable. We do this for both “on” commands and “off” commands.
	} 

	public void offButtonWasPushed(int slot) { 
		offCommands[slot].execute(); 
		undoCommand = offCommands[slot];
	}
	
	public void undoButtonWasPushed() {	undoCommand.undo(); } // When the undo button is pressed, we invoke the undo() method of the command stored in undoCommand. This reverses the operation of the last command executed.

	public String toString() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------Remote Control------ - \n");
		for (int i = 0; i < onCommands.length; i++)
			stringBuff.append("[slot " + i + "] " + onCommands[i].getClass().getName() + " " + offCommands[i].getClass().getName() + "\n");
		return stringBuff.toString(); // We've overwritten toString() to print out each slot and its corresponding command.You'll see us use this when we test the remote control.
	}
}
*/
class RemoteControlWithUndo {
	static constexpr int slots = 7; // The number of slots in the remote control.
	array<shared_ptr<Command>, slots> onCommands;
	array<shared_ptr<Command>, slots> offCommands;
	shared_ptr<Command> undoCommand; // This is where we'll stash the last command executed for the undo button.
public:
	RemoteControlWithUndo() {
		shared_ptr<Command> noCommand = make_shared<NoCommand>(); 
		for (int i = 0; i < slots; ++i) {
			onCommands[i] = noCommand;
			offCommands[i] = noCommand;
		}
		undoCommand = noCommand; // Just like the other slots, undo starts off with a NoCommand, so pressing undo before any other button won't do anything at all.
	}

	void setCommand(int slot, shared_ptr<Command> onCommand, shared_ptr<Command> offCommand) { 
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}

	void onButtonWasPushed(int slot) { 
		onCommands[slot]->execute(); 
		undoCommand = onCommands[slot]; // When a button is pressed, we take the command and first execute it; then we save a reference to it in the undoCommand instance variable. We do this for both “on” commands and “off” commands.
	} 

	void offButtonWasPushed(int slot) { 
		offCommands[slot]->execute(); 
		undoCommand = offCommands[slot];
	}

	void undoButtonWasPushed() { undoCommand->undo(); } // When the undo button is pressed, we invoke the undo() method of the command stored in undoCommand. This reverses the operation of the last command executed.

	string toString() const { // We've overwritten toString() to print out each slot and its corresponding command.You'll see us use this when we test the remote control.
		string result = "\n------Remote Control------ - \n";
		for (int i = 0; i < slots; ++i)
			result += "[slot " + to_string(i) + "] " + typeid(*onCommands[i]).name() + " " + typeid(*offCommands[i]).name() + "\n";
		return result;
	}
};
#pragma endregion //To add support for the undo button
