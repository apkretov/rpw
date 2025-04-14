#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "State.h"
using std::cout;
using std::string;
using std::shared_ptr;
using std::to_string;

#pragma region Sharpen your pencil
class State;

class GumballMachine : public std::enable_shared_from_this<GumballMachine> {
	shared_ptr<State> soldOutState;		// Having the shared_ptr in the State classes requires the overhead:
	shared_ptr<State> noQuarterState;	// 1. The private constructor;
	shared_ptr<State> hasQuarterState;	// 2. The creating and initializing functions due to the inheritance 'from this'.
	shared_ptr<State> soldState;
	shared_ptr<State> winnerState; // All you need to add here is the new WinnerState and initialize it in the constructor.
	shared_ptr<State> state;
	int count;
	void initialize();
	explicit GumballMachine(int numberGumballs);
public:
	GumballMachine(const GumballMachine &) = delete; // Delete copy operations as copying a state machine doesn't make sense
	GumballMachine &operator=(const GumballMachine &) = delete;
	GumballMachine(GumballMachine &&) = delete; // Move operations should also be deleted as it would break shared_from_this
	GumballMachine &operator=(GumballMachine &&) = delete;

	static shared_ptr<GumballMachine> create(int numberGumballs);
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
};
#pragma endregion //Sharpen your pencil
