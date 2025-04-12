#pragma once

#include "State.h"
#include "GumballMachine.h"
using std::string;

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
    GumballMachine* gumballMachine;
public:
    SoldState(GumballMachine* gumballMachine) : gumballMachine(gumballMachine) {}
    void insertQuarter() override { cout << "Please wait, we're already giving you a gumball\n"; }
    void ejectQuarter() override { cout << "Sorry, you already turned the crank\n"; }
    void turnCrank() override { cout << "Turning twice doesn't get you another gumball!\n"; }

    void dispense() override {
        gumballMachine->releaseBall();
        if (gumballMachine->getCount() > 0) gumballMachine->setState(gumballMachine->getNoQuarterState());
        else {
            cout << "Oops, out of gumballs!\n";
            gumballMachine->setState(gumballMachine->getSoldOutState());
        }
    }
    string toString() override { return "dispensing a gumball"; }
};