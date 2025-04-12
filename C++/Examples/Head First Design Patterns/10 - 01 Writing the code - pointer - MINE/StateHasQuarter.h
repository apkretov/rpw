#pragma once

#include <iostream>
#include "State.h"
#include "GumballMachine.h"
using std::cout;
using std::string;

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
    GumballMachine* gumballMachine;
public:
    HasQuarterState(GumballMachine* gumballMachine) : gumballMachine(gumballMachine) {}
    void insertQuarter() override { cout << "You can't insert another quarter\n"; }
    void ejectQuarter() override {
        cout << "Quarter returned\n";
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    }
    void turnCrank() override {
        cout << "You turned...\n";
        gumballMachine->setState(gumballMachine->getSoldState());
    }
    void dispense() override { cout << "No gumball dispensed\n"; }
    string toString() override { return "waiting for turn of crank"; }
};