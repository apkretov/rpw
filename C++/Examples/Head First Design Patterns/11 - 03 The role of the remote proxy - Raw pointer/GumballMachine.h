#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include "GumballMachineI.h"
#include "State.h"

#pragma region Trae
class State;

class GumballMachine : public IGumballMachine {
	using State_ptr = std::unique_ptr<State>;
	State_ptr soldOutState;
	State_ptr noQuarterState;
	State_ptr hasQuarterState;
	State_ptr soldState;
	State_ptr winnerState;
	State *state;  // Raw pointer as observer
	std::string location;
	int count;

public:
	GumballMachine(std::string_view location, int count);
	void insertQuarter() { state->insertQuarter(); }
	void ejectQuarter() { state->ejectQuarter(); }

	void turnCrank() {
		state->turnCrank();
		state->dispense();
	}

	void setState(State *state) { this->state = state; }

	void releaseBall() {
		std::cout << "A gumball comes rolling out the slot..\n";
		if (count > 0)
			--count;
	}

	void refill(int count) {
		this->count = count;
		state = noQuarterState.get();
	}

	State *getState() const { return state; }
	State *getSoldOutState() const { return soldOutState.get(); }
	State *getNoQuarterState() const { return noQuarterState.get(); }
	State *getHasQuarterState() const { return hasQuarterState.get(); }
	State *getSoldState() const { return soldState.get(); }
	State *getWinnerState() const { return winnerState.get(); }

	std::string getLocation() const override { return location; } // IGumballMachine interface implementation
	int getCount() const override { return count; }
	std::string getStateString() const override { return state->toString(); }

	std::string toString() const {
		std::string result;
		result += "\nMighty Gumball, Inc.";
		result += "\nC++-enabled Standing Gumball Model #2004";
		result += "\nInventory: " + std::to_string(count) + " gumball";
		if (count != 1)
			result += "s";
		result += "\n";
		result += "Machine is " + state->toString() + "\n\n";
		return result;
	}
};
#pragma endregion //Trae
