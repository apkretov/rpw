#include "../../stdafx.h"
#include "CommandCeilingFanOff.h"
#include "CommandCeilingFanOn.h"
#include "CommandGarageDoorDown.h"
#include "CommandGarageDoorUp.h"
#include "CommandLightOn.h"
#include "CommandLightOff.h"
#include "CommandNo.h"
#include "CommandStereoOff.h"
#include "CommandStereoOnWithCD.h"
#include "RemoteControlWithUndo.h"
using std::cout;
using std::make_shared;

#pragma region Time to QA that Undo button!
/* Java
public class RemoteLoader {
	public static void main(String[] args) {
		RemoteControlWithUndo remoteControl = new RemoteControlWithUndo();
		Light livingRoomLight = new Light("Living Room"); // Create a Light, and our new undo() enabled Light On and Off Commands.
		LightOnCommand livingRoomLightOn = new LightOnCommand(livingRoomLight);
		LightOffCommand livingRoomLightOff = new LightOffCommand(livingRoomLight);
		
		remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff); // Add the light Commands to the remote in slot 0.

		remoteControl.onButtonWasPushed(0); // Turn the light on, then off and then undo.
		remoteControl.offButtonWasPushed(0);
		System.out.println(remoteControl);
		remoteControl.undoButtonWasPushed();

		remoteControl.offButtonWasPushed(0); // Then, turn the light off, back on and undo.
		remoteControl.onButtonWasPushed(0);
		System.out.println(remoteControl);
		remoteControl.undoButtonWasPushed();
	}
}
*/
int main() {
	print_file_line();

    RemoteControlWithUndo remoteControl;
	Light livingRoomLight("Living Room"); // Create a Light, and our new undo() enabled Light On and Off Commands.
    auto livingRoomLightOn = make_shared<LightOnCommand>(livingRoomLight);
    auto livingRoomLightOff = make_shared<LightOffCommand>(livingRoomLight);

    remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff); // Add the light Commands to the remote in slot 0.

    remoteControl.onButtonWasPushed(0); // Turn the light on, then off and then undo.
    remoteControl.offButtonWasPushed(0);
    cout << remoteControl.toString();
	cout << '\n'; //MINE
    remoteControl.undoButtonWasPushed();
	cout << '\n'; //MINE

    remoteControl.offButtonWasPushed(0); // Then, turn the light off, back on and undo.
    remoteControl.onButtonWasPushed(0);
    cout << remoteControl.toString();
	cout << '\n'; //MINE
    remoteControl.undoButtonWasPushed();

	return 0;
}
#pragma endregion //Time to QA that Undo button!
