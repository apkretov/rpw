#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <memory>
#include "State.h"
#include "GumballMachineI.h"
using std::cout;
using std::shared_ptr;
using std::string;
using std::string_view;
using std::to_string;

class State;

#pragma region Trae
class GumballMachine : public IGumballMachine, public std::enable_shared_from_this<GumballMachine> {
	shared_ptr<State> soldOutState;		// Having the shared_ptr in the State classes requires the overhead:
	shared_ptr<State> noQuarterState;	// 1. The private constructor;
	shared_ptr<State> hasQuarterState;	// 2. The creating and initializing functions due to the inheritance 'from this'.
	shared_ptr<State> soldState;
	shared_ptr<State> winnerState; // All you need to add here is the new WinnerState and initialize it in the constructor.
	shared_ptr<State> state;
	string location;
	int count;
	void initialize();
	GumballMachine(string_view location, int count); // The location is passed into the constructor and stored in the instance variable.
public:
	GumballMachine(const GumballMachine &) = delete; // Delete copy operations as copying a state machine doesn't make sense
	GumballMachine &operator=(const GumballMachine &) = delete;
	GumballMachine(GumballMachine &&) = delete; // Move operations should also be deleted as it would break shared_from_this
	GumballMachine &operator=(GumballMachine &&) = delete;

	static shared_ptr<GumballMachine> create(string_view location, int count);
	void insertQuarter() { state->insertQuarter(); }
	void ejectQuarter() { state->ejectQuarter(); }

	void turnCrank() {
		state->turnCrank();
		state->dispense();
	}

	void setState(shared_ptr<State> state) { this->state = state; }

	void releaseBall() {
		cout << "A gumball comes rolling out the slot..\n";
		if (count > 0)
			--count;
	}

	void refill(int count) {
		this->count = count;
		state = noQuarterState;
	}

	shared_ptr<State> getState() const { return state; }
	shared_ptr<State> getSoldOutState() const { return soldOutState; }
	shared_ptr<State> getNoQuarterState() const { return noQuarterState; }
	shared_ptr<State> getHasQuarterState() const { return hasQuarterState; }
	shared_ptr<State> getSoldState() const { return soldState; }
	shared_ptr<State> getWinnerState() const { return winnerState; } // Don't forget you also have to add a getter method for WinnerState too.
	string getLocation() const { return location; } // Let's also add a getter method to grab the location when we need it.
	int getCount() const { return count; }

	string toString() const {
		string result;
		result += "\nMighty Gumball, Inc.";
		result += "\nC++-enabled Standing Gumball Model #2004";
		result += "\nInventory: " + to_string(count) + " gumball";
		if (count != 1)
			result += "s";
		result += "\n";
		result += "Machine is " + state->toString() + "\n\n";
		return result;
	}

	string getStateString() const override { return state->toString(); } // Add these methods to properly implement IGumballMachine
	string getLocation() const override { return location; }
	int getCount() const override { return count; }
};
#pragma endregion //Trae
