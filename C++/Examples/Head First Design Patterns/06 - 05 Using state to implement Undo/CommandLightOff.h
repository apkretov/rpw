#pragma once

#include "Command.h"
#include "DeviceLight.h"

#pragma region 2 Lets start with the LightOnCommand // 2 Let's start with the LightOnCommand
/* Java
public class LightOffCommand implements Command {
	Light light;
	public LightOffCommand(Light light) { this.light = light; }
	public void execute() { light.off(); }
	public void undo() { light.on(); } // And here, undo() turns the light back on!
}
*/
class LightOffCommand final : public Command {
	Light &light_;
public:
	explicit LightOffCommand(Light &light) : light_(light) {}
	void execute() override { light_.off(); }
	void undo() override { light_.on(); } // And here, undo() turns the light back on!
};
#pragma endregion //2 Lets start with the LightOnCommand
