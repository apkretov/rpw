#pragma once

#include "Command.h"
#include "DeviceCeilingFan.h"

#pragma region Brain Power
class CeilingFanMediumCommand final : public Command {
	CeilingFan &ceilingFan_;
	int prevSpeed_;
public:
	explicit CeilingFanMediumCommand(CeilingFan &ceilingFan) : ceilingFan_(ceilingFan), prevSpeed_(0) {}
	void execute() override { ceilingFan_.medium(); }

	void undo() override {
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
#pragma endregion //Brain Power
