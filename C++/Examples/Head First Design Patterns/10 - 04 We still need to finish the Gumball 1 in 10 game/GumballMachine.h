#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "State.h"
using std::cout;
using std::string;
using std::shared_ptr;
using std::to_string;

#pragma region We still need to finish the Gumball 1 in 10 game
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumballstatewinner
package headfirst.designpatterns.state.gumballstatewinner;

public class GumballMachine {

	State soldOutState;
	State noQuarterState;
	State hasQuarterState;
	State soldState;
	State winnerState;

	State state = soldOutState;
	int count = 0;

	public GumballMachine(int numberGumballs) {
		soldOutState = new SoldOutState(this);
		noQuarterState = new NoQuarterState(this);
		hasQuarterState = new HasQuarterState(this);
		soldState = new SoldState(this);
		winnerState = new WinnerState(this);

		this.count = numberGumballs;
		if (numberGumballs > 0) {
			state = noQuarterState;
		}
	}

	public void insertQuarter() {
		state.insertQuarter();
	}

	public void ejectQuarter() {
		state.ejectQuarter();
	}

	public void turnCrank() {
		state.turnCrank();
		state.dispense();
	}

	void setState(State state) {
		this.state = state;
	}

	void releaseBall() {
		System.out.println("A gumball comes rolling out the slot...");
		if (count > 0) {
			count = count - 1;
		}
	}

	int getCount() {
		return count;
	}

	void refill(int count) {
		this.count += count;
		System.out.println("The gumball machine was just refilled; its new count is: " + this.count);
		state.refill();
	}

	public State getState() {
		return state;
	}

	public State getSoldOutState() {
		return soldOutState;
	}

	public State getNoQuarterState() {
		return noQuarterState;
	}

	public State getHasQuarterState() {
		return hasQuarterState;
	}

	public State getSoldState() {
		return soldState;
	}

	public State getWinnerState() {
		return winnerState;
	}

	public String toString() {
		StringBuffer result = new StringBuffer();
		result.append("\nMighty Gumball, Inc.");
		result.append("\nJava-enabled Standing Gumball Model #2004");
		result.append("\nInventory: " + count + " gumball");
		if (count != 1) {
			result.append("s");
		}
		result.append("\n");
		result.append("Machine is " + state + "\n");
		return result.toString();
	}
}
*/

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

	shared_ptr<State> getState() { return state; }
	shared_ptr<State> getSoldOutState() { return soldOutState; }
	shared_ptr<State> getNoQuarterState() { return noQuarterState; }
	shared_ptr<State> getHasQuarterState() { return hasQuarterState; }
	shared_ptr<State> getSoldState() { return soldState; }
	shared_ptr<State> getWinnerState() { return winnerState; } // Don't forget you also have to add a getter method for WinnerState too.
	int getCount() { return count; }

	string toString() {
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
#pragma endregion //We still need to finish the Gumball 1 in 10 game
