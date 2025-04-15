#pragma once

#include <memory>
#include "GumballMachine.h"
#include "State.h"
using std::cout;
using std::shared_ptr;
using std::string;
using std::weak_ptr;

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
	weak_ptr<GumballMachine> gumballMachine;
public:
	WinnerState(shared_ptr<GumballMachine> gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override { cout << "Please wait, we're already giving you a Gumball\n"; }
	void ejectQuarter() override { cout << "Please wait, we're already giving you a Gumball\n"; }
	void turnCrank() override { cout << "Turning again doesn't get you another gumball!\n"; }

	void dispense() override { // Here we release two gumballs and then either go to the NoQuarterState or the SoldOutState.
		if (auto machine = gumballMachine.lock()) {
			machine->releaseBall();
			if (machine->getCount() == 0)
				machine->setState(machine->getSoldOutState());
			else {
				machine->releaseBall(); // As long as we have a second gumball we release it.
				cout << "YOU'RE A WINNER! You got two gumballs for your quarter\n";
				if (machine->getCount() > 0)
					machine->setState(machine->getNoQuarterState());
				else {
					cout << "Oops, out of gumballs!\n";
					machine->setState(machine->getSoldOutState());
				}
			}
		}
	}

	string toString() override { return "despensing two gumballs for your quarter, because YOU'RE A WINNER!"; }
};
#pragma endregion //We still need to finish the Gumball 1 in 10 game