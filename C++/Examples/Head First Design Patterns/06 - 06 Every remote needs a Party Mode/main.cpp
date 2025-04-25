#include <vector>
#include "vld.h"
#include "../../stdafx.h"
#include "CommandCeilingFanHigh.h"
#include "CommandCeilingFanLow.h"
#include "CommandCeilingFanMedium.h"
#include "CommandCeilingFanOff.h"
#include "CommandGarageDoorDown.h"
#include "CommandGarageDoorUp.h"
#include "CommandHottubOff.h"
#include "CommandHottubOn.h"
#include "CommandLightOn.h"
#include "CommandLightOff.h"
#include "CommandTVOff.h"
#include "CommandTVOn.h"
#include "CommandMacro.h"
#include "CommandNo.h"
#include "CommandStereoOff.h"
#include "CommandStereoOn.h"
#include "RemoteControlWithUndo.h"
using std::cout;
using std::make_shared;
using std::shared_ptr;
using std::vector;

#pragma region Using a macro command
/* Java
Light light = new Light("Living Room"); // Create all the devices, a light, tv, stereo, and hot tub.
TV tv = new TV("Living Room");
Stereo stereo = new Stereo("Living Room");
Hottub hottub = new Hottub();

LightOnCommand lightOn = new LightOnCommand(light); // Now create all the On commands to control them.
StereoOnCommand stereoOn = new StereoOnCommand(stereo);
TVOnCommand tvOn = new TVOnCommand(tv);
HottubOnCommand hottubOn = new HottubOnCommand(hottub);
#pragma endregion //Using a macro command

Command[] partyOn = {lightOn, stereoOn, tvOn, hottubOn}; // Create an array for On and an array for Off commands...
Command[] partyOff = {lightOff, stereoOff, tvOff, hottubOff};

MacroCommand partyOnMacro = new MacroCommand(partyOn); // ...and create two corresponding macros to hold them.
MacroCommand partyOffMacro = new MacroCommand(partyOff);

remoteControl.setCommand(0, partyOnMacro, partyOffMacro); // Assign the macro command to a button as we would any command.

System.out.println(remoteControl); // Finally, we just need to push some buttons and see if this works.
System.out.println("-- - Pushing Macro On-- - ");
remoteControl.onButtonWasPushed(0);
System.out.println("-- - Pushing Macro Off-- - ");
remoteControl.offButtonWasPushed(0);
*/
int main() {
	print_file_line();

	RemoteControlWithUndo remoteControl;

	Light light("Living Room"); // Create all the devices, a light, tv, stereo, and hot tub.
	TV tv("Living Room");
	Stereo stereo("Living Room");
	Hottub hottub;

    auto lightOn = make_shared<LightOnCommand>(light); // Now create all the On commands to control them.
    auto stereoOn = make_shared<StereoOnCommand>(stereo);
    auto tvOn = make_shared<TVOnCommand>(tv);
    auto hottubOn = make_shared<HottubOnCommand>(hottub);

#pragma region Sharpen your pencil
	auto lightOff = make_shared<LightOffCommand>(light);
	auto stereoOff = make_shared<StereoOffCommand>(stereo);
	auto tvOff = make_shared<TVOffCommand>(tv);
	auto hottubOff = make_shared<HottubOffCommand>(hottub);
#pragma endregion //Sharpen your pencil

    vector<shared_ptr<Command>> partyOn = {lightOn, stereoOn, tvOn, hottubOn}; // Create an array for On and an array for Off commands...
    vector<shared_ptr<Command>> partyOff = {lightOff, stereoOff, tvOff, hottubOff};

    auto partyOnMacro = make_shared<MacroCommand>(partyOn); // ...and create two corresponding macros to hold them.
    auto partyOffMacro = make_shared<MacroCommand>(partyOff);

    remoteControl.setCommand(0, partyOnMacro, partyOffMacro); // Assign the macro command to a button as we would any command.

    cout << remoteControl.toString(); // Finally, we just need to push some buttons and see if this works.
	remoteControl.undoButtonWasPushed(); //MINE: A unit-test for the undo button.
    cout << "\n--- Pushing Macro On---\n";
    remoteControl.onButtonWasPushed(0);
    cout << "\n--- Pushing Macro Off---\n";
    remoteControl.offButtonWasPushed(0);

	cout << '\n';
	return 0;
}
#pragma endregion //Using a macro command