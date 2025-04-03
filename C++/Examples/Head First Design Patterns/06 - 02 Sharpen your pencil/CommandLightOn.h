#pragma once

#include "Command.h"
#include "Light.h"

#pragma region Implementing a Command to turn a light on
/* Java
public class LightOnCommand implements Command { // This is a command, so we need to implement the Command interface.
	Light light;
	public LightOnCommand(Light light) { this.light = light; } // The constructor is passed the specific light that this command is going to control - say the living room light - and stashes it in the light instance variable.When execute gets called, this is the light object that is going to be the Receiver of the request.
	public void execute() { light.on(); } // The execute method calls the on() method on the receiving object, which is the light we are controlling.
}
*/
class LightOnCommand final : public Command { // This is a command, so we need to implement the Command interface.
	Light &light_;
public:
	explicit LightOnCommand(Light &light) : light_(light) {} // The constructor is passed the specific light that this command is going to control - say the living room light - and stashes it in the light instance variable.When execute gets called, this is the light object that is going to be the Receiver of the request.
	void execute() override { light_.on(); } // The execute method calls the on() method on the receiving object, which is the light we are controlling.
};
#pragma endregion //Implementing a Command to turn a light on
