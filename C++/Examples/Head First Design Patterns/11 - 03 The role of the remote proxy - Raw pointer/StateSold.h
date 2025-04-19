#pragma once

#include "State.h"
#include "GumballMachine.h"
#include <memory>

#pragma region Implementing more states
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumball
public class SoldState implements State {
	GumballMachine gumballMachine;
	public SoldState(GumballMachine gumballMachine) { this.gumballMachine = gumballMachine; }
	public void insertQuarter() { System.out.println("Please wait, we're already giving you a gumball"); }
	public void ejectQuarter() { System.out.println("Sorry, you already turned the crank"); }
	public void turnCrank() { System.out.println("Turning twice doesn't get you another gumball!"); }
	public void dispense() {
		gumballMachine.releaseBall();
		if (gumballMachine.getCount() > 0) gumballMachine.setState(gumballMachine.getNoQuarterState());
		else {
			System.out.println("Oops, out of gumballs!");
			gumballMachine.setState(gumballMachine.getSoldOutState());
		}
	}
	public String toString() { return "dispensing a gumball"; }
}
*/
class SoldState : public State {
	std::weak_ptr<GumballMachine> gumballMachine;
public:
	SoldState(std::shared_ptr<GumballMachine> gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override { std::cout << "Please wait, we're already giving you a gumball\n"; }
	void ejectQuarter() override { std::cout << "Sorry, you already turned the crank\n"; }
	void turnCrank() override { std::cout << "Turning twice doesn't get you another gumball!\n"; }

	void dispense() override {
		if (auto machine = gumballMachine.lock()) {
			machine->releaseBall();
			if (machine->getCount() > 0)
				machine->setState(machine->getNoQuarterState());
			else {
				std::cout << "Oops, out of gumballs!\n";
				machine->setState(machine->getSoldOutState());
			}
		}
	}
	std::string toString() override { return "dispensing a gumball"; }
};
#pragma endregion //Implementing more states
