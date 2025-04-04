#pragma once

#include "Command.h"
#include "DeviceCeilingFan.h"

#pragma region Adding Undo to the ceiling fan commands
/* Java
public class CeilingFanHighCommand implements Command {
	CeilingFan ceilingFan;
	int prevSpeed; // We've added local state to keep track of the previous speed of the fan.

	public CeilingFanHighCommand(CeilingFan ceilingFan) { this.ceilingFan = ceilingFan; }

	public void execute() {
		prevSpeed = ceilingFan.getSpeed(); // In execute, before we change the speed of the fan, we need to first record its previous state, just in case we need to undo our actions.
		ceilingFan.high();
	}
	
	public void undo() { // To undo, we set the speed of the fan back to its previous speed.
		if (prevSpeed == CeilingFan.HIGH)
			ceilingFan.high();
		else if (prevSpeed == CeilingFan.MEDIUM)
			ceilingFan.medium();
		else if (prevSpeed == CeilingFan.LOW)
			ceilingFan.low();
		else if (prevSpeed == CeilingFan.OFF)
			ceilingFan.off();
	}
}
*/
class CeilingFanHighCommand final : public Command {
    CeilingFan& ceilingFan_;
    int prevSpeed_; // We've added local state to keep track of the previous speed of the fan.
public:
    explicit CeilingFanHighCommand(CeilingFan& ceilingFan) : ceilingFan_(ceilingFan), prevSpeed_(0) {}

    void execute() override {
        prevSpeed_ = ceilingFan_.getSpeed(); // In execute, before we change the speed of the fan, we need to first record its previous state, just in case we need to undo our actions.
        ceilingFan_.high();
    }

    void undo() override { // To undo, we set the speed of the fan back to its previous speed.
        if (prevSpeed_ == CeilingFan::HIGH)
            ceilingFan_.high();
        else if (prevSpeed_ == CeilingFan::MEDIUM)
            ceilingFan_.medium();
        else if (prevSpeed_ == CeilingFan::LOW)
            ceilingFan_.low();
        else if (prevSpeed_ == CeilingFan::OFF)
            ceilingFan_.off();
    }
};
#pragma endregion //Adding Undo to the ceiling fan commands
