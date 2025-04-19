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
    GumballMachine &gumballMachine;
	Rnd randomWinner; // First we add a random number generator to generate the 10% chance of winning...
public:
	HasQuarterState(GumballMachine *gumballMachine) : gumballMachine(*gumballMachine) {}
	void insertQuarter() override { std::cout << "You can't insert another quarter\n"; }

    void ejectQuarter() override {
        std::cout << "Quarter returned\n";
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    }

    void turnCrank() override {
        std::cout << "You turned...\n";
        int winner = randomWinner(); // ...then we determine if this customer won.
        if ((winner == 0) && (gumballMachine.getCount() > 1)) // If they won, and there's enough gumballs left for them to get two, we go to the WinnerState; otherwise, we go to the SoldState(just like we always did).
            gumballMachine.setState(gumballMachine.getWinnerState());
        else
            gumballMachine.setState(gumballMachine.getSoldState());
    }

    void dispense() override { std::cout << "No gumball dispensed\n"; }
    std::string toString() override { return "waiting for turn of crank"; }
};
#pragma endregion //Finishing the game
