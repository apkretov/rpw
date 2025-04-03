#pragma once

#include <memory>
#include "Command.h"
using namespace std;

#pragma region Using the command object
/* Java
public class SimpleRemoteControl {
	Command slot; // We have one slot to hold our command, which will control one device.
	public SimpleRemoteControl() {}
	public void setCommand(Command command) { slot = command; } // We have a method for setting the command the slot is going to control. This could be called multiple times if the client of this code wanted to change the behavior of the remote button.
	public void buttonWasPressed() { slot.execute(); } // This method is called when the button is pressed.All we do is take the current command bound to the slot and call its execute() method.
}
*/
class SimpleRemoteControl {
private:
	shared_ptr<Command> slot; // We have one slot to hold our command, which will control one device.
public:
	void setCommand(shared_ptr<Command> command) { slot = command; } // We have a method for setting the command the slot is going to control. This could be called multiple times if the client of this code wanted to change the behavior of the remote button.
	void buttonWasPressed() { slot->execute(); } // This method is called when the button is pressed. All we do is take the current command bound to the slot and call its execute() method.
};
#pragma endregion //Using the command object
