#pragma once

#include <iostream>
#include "State.h"
#include "GumballMachine.h"

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
    GumballMachine* gumballMachine;
public:
    NoQuarterState(GumballMachine* gumballMachine) : gumballMachine(gumballMachine) {}

    void insertQuarter() override {
        std::cout << "You inserted a quarter\n";
        gumballMachine->setState(gumballMachine->getHasQuarterState());
    }

	void ejectQuarter() override { std::cout << "You haven't inserted a quarter\n"; }
	void turnCrank() override { std::cout << "You turned, but there's no quarter\n"; }
	void dispense() override { std::cout << "You need to pay first\n"; }
	std::string toString() override { return "waiting for quarter"; }
};
#pragma endregion //Implementing our State classes
