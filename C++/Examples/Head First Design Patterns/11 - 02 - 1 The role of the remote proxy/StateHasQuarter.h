#pragma once

#include <iostream>
#include <memory>
#include "../../stdafx.h"
#include "GumballMachine.h"
#include "State.h"

#pragma region Finishing the game
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumballstatewinner
public class HasQuarterState implements State {
	Random randomWinner = new Random(System.currentTimeMillis()); // First we add a random number generator to generate the 10% chance of winning...
	GumballMachine gumballMachine;
	public HasQuarterState(GumballMachine gumballMachine) { this.gumballMachine = gumballMachine; }
	public void insertQuarter() { System.out.println("You can't insert another quarter"); }
	public void ejectQuarter() {
		System.out.println("Quarter returned");
		gumballMachine.setState(gumballMachine.getNoQuarterState());
	}
	public void turnCrank() {
		System.out.println("You turned...");
		int winner = randomWinner.nextInt(10); // ...then we determine if this customer won.
		if ((winner == 0) && (gumballMachine.getCount() > 1)) { // If they won, and there's enough gumballs left for them to get two, we go to the WinnerState; otherwise, we go to the SoldState(just like we always did).
			gumballMachine.setState(gumballMachine.getWinnerState());
		} else
			gumballMachine.setState(gumballMachine.getSoldState());
	}
	public void dispense() { System.out.println("No gumball dispensed"); }
	public String toString() { return "waiting for turn of crank"; }
}
*/
class HasQuarterState : public State {
	Rnd randomWinner; // First we add a random number generator to generate the 10% chance of winning...
	std::weak_ptr<GumballMachine> gumballMachine;
public:
	HasQuarterState(std::shared_ptr<GumballMachine> gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override { std::cout << "You can't insert another quarter\n"; }

	void ejectQuarter() override {
		if (auto machine = gumballMachine.lock()) {
			std::cout << "Quarter returned\n";
			machine->setState(machine->getNoQuarterState());
		}
	}

	void turnCrank() override {
		if (auto machine = gumballMachine.lock()) {
			std::cout << "You turned...\n";
			int winner = randomWinner(); // ...then we determine if this customer won.
			if ((winner == 0) && (machine->getCount() > 1)) { // If they won, and there's enough gumballs left for them to get two, we go to the WinnerState; otherwise, we go to the SoldState(just like we always did).
				machine->setState(machine->getWinnerState());
			} else
				machine->setState(machine->getSoldState());
		}
	}

	void dispense() override { std::cout << "No gumball dispensed\n"; }
	std::string toString() override { return "waiting for turn of crank"; }
};
#pragma endregion //Finishing the game