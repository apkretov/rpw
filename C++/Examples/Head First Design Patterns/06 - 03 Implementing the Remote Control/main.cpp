#include "../../stdafx.h"
#include "CommandGarageDoorOpen.h"
#include "CommandLightOn.h"
#include "SimpleRemoteControl.h"
using namespace std;

#pragma region Sharpen your pencil
/* Java
public class RemoteControlTest {
	public static void main(String[] args) {
		SimpleRemoteControl remote = new SimpleRemoteControl();
		Light light = new Light();
		GarageDoor garageDoor = new GarageDoor();
		LightOnCommand lightOn = new LightOnCommand(light);
		GarageDoorOpenCommand garageOpen = new GarageDoorOpenCommand(garageDoor);
		remote.setCommand(lightOn);
		remote.buttonWasPressed();
		remote.setCommand(garageOpen);
		remote.buttonWasPressed();
	}
}
*/
int main() {
	print_file_line();

	SimpleRemoteControl remote;
	Light light;
	GarageDoor garageDoor;
	auto lightOn = make_shared<LightOnCommand>(light);
	auto garageOpen = make_shared<GarageDoorOpenCommand>(garageDoor);

	remote.setCommand(lightOn);
	remote.buttonWasPressed();
	remote.setCommand(garageOpen);
	remote.buttonWasPressed();

	return 0;
}
#pragma endregion //Sharpen your pencil
