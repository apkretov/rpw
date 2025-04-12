#pragma once

#include <iostream>
#include "State.h"
#include "GumballMachine.h"
#include <memory>
using std::cout;
using std::shared_ptr;
using std::string;
using std::weak_ptr;

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumball
public class HasQuarterState implements State {
    GumballMachine gumballMachine;
    public HasQuarterState(GumballMachine gumballMachine) { this.gumballMachine = gumballMachine; }
    public void insertQuarter() { System.out.println("You can't insert another quarter"); }
    public void ejectQuarter() {
        System.out.println("Quarter returned");
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    }
    public void turnCrank() {
        System.out.println("You turned...");
        gumballMachine.setState(gumballMachine.getSoldState());
    }
    public void dispense() { System.out.println("No gumball dispensed"); }
    public String toString() { return "waiting for turn of crank"; }
}
*/

class HasQuarterState : public State {
    weak_ptr<GumballMachine> gumballMachine;
public:
    HasQuarterState(shared_ptr<GumballMachine> gumballMachine) : gumballMachine(gumballMachine) {}
    void insertQuarter() override { cout << "You can't insert another quarter\n"; }

	void ejectQuarter() override {
		if (auto machine = gumballMachine.lock()) {
			cout << "Quarter returned\n";
#ifdef OFF
			machine->setState(machine->getNoQuarterState());
#endif //OFF
		}
	}
    
	void turnCrank() override {
		if (auto machine = gumballMachine.lock()) {
			cout << "You turned...\n";
#ifdef OFF
			machine->setState(machine->getSoldState());
#endif //OFF
		}
    }
    
	void dispense() override { cout << "No gumball dispensed\n"; }
    string toString() override { return "waiting for turn of crank"; }
};