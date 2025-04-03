#pragma once

#include "Command.h"
#include "DeviceLight.h"

#pragma region Implementing the Commands
/* Java
public class LightOffCommand implements Command { 
	Light light;
	public LightOffCommand(Light light) { this.light = light; } 
	public void execute() { light.off(); } // The LightOffCommand works exactly the same way as the LightOnCommand, except that we are binding the receiver to a different action : the off() method.
}
*/
class LightOffCommand final : public Command {
	Light &light_;
public:
	explicit LightOffCommand(Light &light) : light_(light) {} 
	void execute() override { light_.off(); } // The LightOffCommand works exactly the same way as the LightOnCommand, except that we are binding the receiver to a different action : the off() method.
};
#pragma endregion //Implementing the Commands
