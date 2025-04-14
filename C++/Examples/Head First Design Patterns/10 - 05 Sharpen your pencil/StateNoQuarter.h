#pragma once

#include <iostream>
#include "State.h"
#include "GumballMachine.h"
#include <memory>
using std::cout;
using std::shared_ptr;
using std::string;

#pragma region Implementing our State classes
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumball
public class NoQuarterState implements State {
	GumballMachine gumballMachine;
	public NoQuarterState(GumballMachine gumballMachine) { this.gumballMachine = gumballMachine; }
	public void insertQuarter() {
		System.out.println("You inserted a quarter");
		gumballMachine.setState(gumballMachine.getHasQuarterState());
	}
	public void ejectQuarter() { System.out.println("You haven't inserted a quarter"); }
	public void turnCrank() { System.out.println("You turned, but there's no quarter"); }
	public void dispense() { System.out.println("You need to pay first"); }
	public String toString() { return "waiting for quarter"; }
}
*/
class NoQuarterState : public State {
	weak_ptr<GumballMachine> gumballMachine;
public:
	NoQuarterState(shared_ptr<GumballMachine> gumballMachine) : gumballMachine(gumballMachine) {}

	void insertQuarter() override {
		if (auto machine = gumballMachine.lock()) {
			cout << "You inserted a quarter\n";
			machine->setState(machine->getHasQuarterState());
		}
	}

	void ejectQuarter() override { cout << "You haven't inserted a quarter\n"; }
	void turnCrank() override { cout << "You turned, but there's no quarter\n"; }
	void dispense() override { cout << "You need to pay first\n"; }
	string toString() override { return "waiting for quarter"; }
};
#pragma endregion //Implementing our State classes
