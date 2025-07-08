#include "../../stdafx.h"
//OFF #include "vld.h"
#include "CommandLightOn.h"
#include "SimpleRemoteControl.h"
using namespace std;

#pragma region Creating a simple test to use the Remote Control
/* Java
public class RemoteControlTest { // This is our Client in Command Pattern-speak.
	public static void main(String[] args) {
		SimpleRemoteControl remote = new SimpleRemoteControl(); // The remote is our Invoker; it will be passed a command object that can be used to make requests.
		Light light = new Light(); // Now we create a Light object, this will be the Receiver of the request.
		LightOnCommand lightOn = new LightOnCommand(light); // Here, create a command and pass the Receiver to it.
		remote.setCommand(lightOn); // Here, pass the command to the Invoker.
		remote.buttonWasPressed(); // And then we simulate the button being pressed.
	}
}
*/
int main() { // This is our Client in Command Pattern-speak.
	print_file_line();

	SimpleRemoteControl remote; // The remote is our Invoker; it will be passed a command object that can be used to make requests.
	Light light; // Now we create a Light object, this will be the Receiver of the request.
	auto lightOn = make_shared<LightOnCommand>(light); // Here, create a command and pass the Receiver to it.
	remote.setCommand(lightOn); // Here, pass the command to the Invoker.
	remote.buttonWasPressed(); // And then we simulate the button being pressed.

	return 0;
}
#pragma endregion //Creating a simple test to use the Remote Control