#pragma once

#include "Command.h"
#include "DeviceLight.h"

#pragma region 2 Let's start with the LightOnCommand
/* Java
public class LightOnCommand implements Command {
	Light light;
	public LightOnCommand(Light light) { this.light = light; } 
	public void execute() { light.on(); } 
	public void undo() { light.off(); } // execute() turns the light on, so undo() simply turns the light back off.
}
*/
class LightOnCommand final : public Command {
	Light &light_;
public:
	explicit LightOnCommand(Light &light) : light_(light) {} 
	void execute() override { light_.on(); } 
	void undo() override { light_.off(); } // execute() turns the light on, so undo() simply turns the light back off.
};
#pragma endregion //2 Let's start with the LightOnCommand