#include "../../stdafx.h"
#include "CommandCeilingFanOn.h"
#include "CommandGarageDoorOpen.h"
#include "CommandLightOn.h"
#include "CommandLightOff.h"
#include "CommandNo.h"
#include "CommandStereoOnWithCD.h"
#include "RemoteControl.h"
using namespace std;

#pragma region Putting the Remote Control through its paces
/* Java
public class RemoteLoader {
	public static void main(String[] args) {
		RemoteControl remoteControl = new RemoteControl();
		
		Light livingRoomLight = new Light(�Living Room�); // Create all the devices in their proper locations.
		Light kitchenLight = new Light(�Kitchen�);
		CeilingFan ceilingFan = new CeilingFan(�Living Room�);
		GarageDoor garageDoor = new GarageDoor(��);
		Stereo stereo = new Stereo(�Living Room�);
		
		LightOnCommand livingRoomLightOn = new LightOnCommand(livingRoomLight); // Create all the Light Command objects.
		LightOffCommand livingRoomLightOff = new LightOffCommand(livingRoomLight);
		LightOnCommand kitchenLightOn = new LightOnCommand(kitchenLight);
		LightOffCommand kitchenLightOff = new LightOffCommand(kitchenLight);

		CeilingFanOnCommand ceilingFanOn = new CeilingFanOnCommand(ceilingFan); // Create the On and Off for the ceiling fan.
		CeilingFanOffCommand ceilingFanOff = new CeilingFanOffCommand(ceilingFan);

		GarageDoorUpCommand garageDoorUp = new GarageDoorUpCommand(garageDoor); // Create the Up and Down commands for the Garage.
		GarageDoorDownCommand garageDoorDown = new GarageDoorDownCommand(garageDoor);
		
		StereoOnWithCDCommand stereoOnWithCD = new StereoOnWithCDCommand(stereo); // Create the stereo On and Off commands.
		StereoOffCommand stereoOff = new StereoOffCommand(stereo);
		
		remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff); // Now that we�ve got all our commands, we can load them into the remote slots.
		remoteControl.setCommand(1, kitchenLightOn, kitchenLightOff);
		remoteControl.setCommand(2, ceilingFanOn, ceilingFanOff);
		remoteControl.setCommand(3, stereoOnWithCD, stereoOff);

		System.out.println(remoteControl); // Here�s where we use our toString() method to print each remote slot and the command that it is assigned to.

		remoteControl.onButtonWasPushed(0); // All right, we are ready to roll! Now, we step through each slot and push its On and Off button.
		remoteControl.offButtonWasPushed(0);
		remoteControl.onButtonWasPushed(1);
		remoteControl.offButtonWasPushed(1);
		remoteControl.onButtonWasPushed(2);
		remoteControl.offButtonWasPushed(2);
		remoteControl.onButtonWasPushed(3);
		remoteControl.offButtonWasPushed(3);
	}
}
*/
int main() {
    print_file_line();

    RemoteControl remoteControl;

    Light livingRoomLight("Living Room"); // Create all the devices in their proper locations
    Light kitchenLight("Kitchen");
    CeilingFan ceilingFan("Living Room");
    GarageDoor garageDoor("");
    Stereo stereo("Living Room");

    auto livingRoomLightOn = make_shared<LightOnCommand>(livingRoomLight); // Create all the Light Command objects
    auto livingRoomLightOff = make_shared<LightOffCommand>(livingRoomLight);
    auto kitchenLightOn = make_shared<LightOnCommand>(kitchenLight);
    auto kitchenLightOff = make_shared<LightOffCommand>(kitchenLight);

    auto ceilingFanOn = make_shared<CeilingFanOnCommand>(ceilingFan); // Create the On and Off for the ceiling fan
    auto ceilingFanOff = make_shared<CeilingFanOffCommand>(ceilingFan);

    auto garageDoorUp = make_shared<GarageDoorUpCommand>(garageDoor); // Create the Up and Down commands for the Garage
    auto garageDoorDown = make_shared<GarageDoorDownCommand>(garageDoor);

    auto stereoOnWithCD = make_shared<StereoOnWithCDCommand>(stereo); // Create the stereo On and Off commands
    auto stereoOff = make_shared<StereoOffCommand>(stereo);

    remoteControl.setCommand(0, livingRoomLightOn, livingRoomLightOff); // Now that we've got all our commands, we can load them into the remote slots
    remoteControl.setCommand(1, kitchenLightOn, kitchenLightOff);
    remoteControl.setCommand(2, ceilingFanOn, ceilingFanOff);
    remoteControl.setCommand(3, stereoOnWithCD, stereoOff);

    cout << remoteControl << '\n'; // Here's where we use our toString() method to print each remote slot and the command that it is assigned to

    remoteControl.onButtonWasPushed(0); // All right, we are ready to roll! Now, we step through each slot and push its On and Off button
    remoteControl.offButtonWasPushed(0);
    remoteControl.onButtonWasPushed(1);
    remoteControl.offButtonWasPushed(1);
    remoteControl.onButtonWasPushed(2);
    remoteControl.offButtonWasPushed(2);
    remoteControl.onButtonWasPushed(3);
    remoteControl.offButtonWasPushed(3);

    return 0;
}
#pragma endregion //Putting the Remote Control through its paces
