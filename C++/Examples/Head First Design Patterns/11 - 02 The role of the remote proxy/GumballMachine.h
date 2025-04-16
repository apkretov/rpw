#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include "GumballMachineI.h"
#include "State.h"

class State;

#pragma region Trae
class GumballMachine : public IGumballMachine, public std::enable_shared_from_this<GumballMachine> {
	std::shared_ptr<State> soldOutState;		// Having the std::shared_ptr in the State classes requires the overhead:
	std::shared_ptr<State> noQuarterState;	// 1. The private constructor;
	std::shared_ptr<State> hasQuarterState;	// 2. The creating and initializing functions due to the inheritance 'from this'.
	std::shared_ptr<State> soldState;
	std::shared_ptr<State> winnerState; // All you need to add here is the new WinnerState and initialize it in the constructor.
	std::shared_ptr<State> state;
	std::string location;
	int count;
	void initialize();
	GumballMachine(std::string_view location, int count); // The location is passed into the constructor and stored in the instance variable.
public:
	GumballMachine(const GumballMachine &) = delete; // Delete copy operations as copying a state machine doesn't make sense
	GumballMachine &operator=(const GumballMachine &) = delete;
	GumballMachine(GumballMachine &&) = delete; // Move operations should also be deleted as it would break shared_from_this
	GumballMachine &operator=(GumballMachine &&) = delete;

	static std::shared_ptr<GumballMachine> create(std::string_view location, int count);
	void insertQuarter() { state->insertQuarter(); }
	void ejectQuarter() { state->ejectQuarter(); }

	void turnCrank() {
		state->turnCrank();
		state->dispense();
	}

	void setState(std::shared_ptr<State> state) { this->state = state; }

	void releaseBall() {
		std::cout << "A gumball comes rolling out the slot..\n";
		if (count > 0)
			--count;
	}

	void refill(int count) {
		this->count = count;
		state = noQuarterState;
	}

	std::shared_ptr<State> getState() const { return state; }
	std::shared_ptr<State> getSoldOutState() const { return soldOutState; }
	std::shared_ptr<State> getNoQuarterState() const { return noQuarterState; }
	std::shared_ptr<State> getHasQuarterState() const { return hasQuarterState; }
	std::shared_ptr<State> getSoldState() const { return soldState; }
	std::shared_ptr<State> getWinnerState() const { return winnerState; } // Don't forget you also have to add a getter method for WinnerState too.
	std::string getLocation() const override { return location; } // Let's also add a getter method to grab the location when we need it.
	int getCount() const override { return count; }
	std::string getStateString() const override { return state->toString(); } // Add these methods to properly implement IGumballMachine
#ifdef OFF
	std::string getLocation() const override { return location; }
	int getCount() const override { return count; }
#endif //OFF

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
