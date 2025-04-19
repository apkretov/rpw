#pragma once

#include <memory>
#include "GumballMachine.h"
#include "State.h"

#pragma region We still need to finish the Gumball 1 in 10 game
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumballstatewinner
package headfirst.designpatterns.state.gumballstatewinner;

public class WinnerState implements State {
	GumballMachine gumballMachine;

	public WinnerState(GumballMachine gumballMachine) { this.gumballMachine = gumballMachine; }
	public void insertQuarter() { System.out.println("Please wait, we're already giving you a Gumball"); }
	public void ejectQuarter() { System.out.println("Please wait, we're already giving you a Gumball"); }
	public void turnCrank() { System.out.println("Turning again doesn't get you another gumball!"); }

	public void dispense() {
		gumballMachine.releaseBall();
		if (gumballMachine.getCount() == 0)
			gumballMachine.setState(gumballMachine.getSoldOutState());
		else {
			gumballMachine.releaseBall();
			System.out.println("YOU'RE A WINNER! You got two gumballs for your quarter");
			if (gumballMachine.getCount() > 0)
				gumballMachine.setState(gumballMachine.getNoQuarterState());
			else {
				System.out.println("Oops, out of gumballs!");
				gumballMachine.setState(gumballMachine.getSoldOutState());
			}
		}
	}

	public void refill() { }
	public String toString() { return "despensing two gumballs for your quarter, because YOU'RE A WINNER!"; }
}
*/
class WinnerState : public State {
    GumballMachine* gumballMachine;
public:
	WinnerState(GumballMachine *gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override { std::cout << "Please wait, we're already giving you a Gumball\n"; }
	void ejectQuarter() override { std::cout << "Please wait, we're already giving you a Gumball\n"; }
	void turnCrank() override { std::cout << "Turning again doesn't get you another gumball!\n"; }

	void dispense() override { // Here we release two gumballs and then either go to the NoQuarterState or the SoldOutState.
		gumballMachine->releaseBall();
		if (gumballMachine->getCount() == 0)
			gumballMachine->setState(gumballMachine->getSoldOutState());
		else {
			gumballMachine->releaseBall(); // As long as we have a second gumball we release it.
			std::cout << "YOU'RE A WINNER! You got two gumballs for your quarter\n";
			if (gumballMachine->getCount() > 0)
				gumballMachine->setState(gumballMachine->getNoQuarterState());
			else {
				std::cout << "Oops, out of gumballs!\n";
				gumballMachine->setState(gumballMachine->getSoldOutState());
			}
		}
	}

	std::string toString() override { return "despensing two gumballs for your quarter, because YOU'RE A WINNER!"; }
};
#pragma endregion //We still need to finish the Gumball 1 in 10 game