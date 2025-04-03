#pragma once

#include "Command.h"
#include "Stereo.h"

#pragma region Implementing the Commands
/* Java
public class StereoOnWithCDCommand implements Command {
	Stereo stereo;
	public StereoOnWithCDCommand(Stereo stereo) { this.stereo = stereo; } // Just like the LightOnCommand, we get passed the instance of the stereo we are going to be controlling and we store it in a local instance variable.

	public void execute() { // To carry out this request, we need to call three methods on the stereo : first, turn it on, then set it to play the CD, and finally set the volume to 11. Why 11 ? Well, it’s better than 10, right ?
		stereo.on();
		stereo.setCD();
		stereo.setVolume(11);
	}
}
*/
class StereoOnWithCDCommand final : public Command {
    Stereo &stereo_;
public:
    explicit StereoOnWithCDCommand(Stereo &stereo) : stereo_(stereo) {} // Just like the LightOnCommand, we get passed the instance of the stereo we are going to be controlling and we store it in a local instance variable.

	void execute() override { // To carry out this request, we need to call three methods on the stereo : first, turn it on, then set it to play the CD, and finally set the volume to 11. Why 11 ? Well, it’s better than 10, right ?
        stereo_.on();
        stereo_.setCD();
        stereo_.setVolume(11);
    }
};
#pragma endregion //Implementing the Commands
