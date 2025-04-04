#include "../../stdafx.h"
#include "CommandCeilingFanHigh.h"
#include "CommandCeilingFanLow.h"
#include "CommandCeilingFanMedium.h"
#include "CommandCeilingFanOff.h"
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

#pragma region Get ready to test the ceiling fan
/* Java
public class RemoteLoader {
	public static void main(String[] args) {
		RemoteControlWithUndo remoteControl = new RemoteControlWithUndo();
		CeilingFan ceilingFan = new CeilingFan(�Living Room�);

		CeilingFanMediumCommand ceilingFanMedium = new CeilingFanMediumCommand(ceilingFan); // Here we instantiate three commands: high, medium, and off.
		CeilingFanHighCommand ceilingFanHigh = new CeilingFanHighCommand(ceilingFan);
		CeilingFanOffCommand ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

		remoteControl.setCommand(0, ceilingFanMedium, ceilingFanOff); // Here we put medium in slot zero, and high in slot one. We also load up the off commands.
		remoteControl.setCommand(1, ceilingFanHigh, ceilingFanOff);

		remoteControl.onButtonWasPushed(0); // First, turn the fan on medium.
		remoteControl.offButtonWasPushed(0); // Then turn it off.
		System.out.println(remoteControl);
		remoteControl.undoButtonWasPushed(); // Undo! It should go back to medium...

		remoteControl.onButtonWasPushed(1); // Turn it on to high this time.
		System.out.println(remoteControl);
		remoteControl.undoButtonWasPushed(); // And, one more undo; it should go back to medium.
	}
}
*/
int main() {
    print_file_line();

    RemoteControlWithUndo remoteControl;
    CeilingFan ceilingFan("Living Room");

    auto ceilingFanMedium = make_shared<CeilingFanMediumCommand>(ceilingFan); // Here we instantiate three commands: high, medium, and off.
    auto ceilingFanHigh = make_shared<CeilingFanHighCommand>(ceilingFan);
    auto ceilingFanOff = make_shared<CeilingFanOffCommand>(ceilingFan);

    remoteControl.setCommand(0, ceilingFanMedium, ceilingFanOff); // Here we put medium in slot zero, and high in slot one. We also load up the off commands.
    remoteControl.setCommand(1, ceilingFanHigh, ceilingFanOff);

    remoteControl.onButtonWasPushed(0); // First, turn the fan on medium.
    remoteControl.offButtonWasPushed(0); // Then turn it off.
    cout << remoteControl.toString();
    cout << '\n'; //MINE
    remoteControl.undoButtonWasPushed(); // Undo! It should go back to medium...
    cout << '\n'; //MINE

    remoteControl.onButtonWasPushed(1); // Turn it on to high this time.
    cout << remoteControl.toString();
    cout << '\n'; //MINE
    remoteControl.undoButtonWasPushed(); // And, one more undo; it should go back to medium.

    return 0;
}
#pragma endregion //Get ready to test the ceiling fan
