#pragma once

#include <iostream>
#include "State.h"
#include "GumballMachine.h"
using std::cout;
using std::string;

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
        cout << "You inserted a quarter\n";
        gumballMachine->setState(gumballMachine->getHasQuarterState());
    }
    void ejectQuarter() override { cout << "You haven't inserted a quarter\n"; }
    void turnCrank() override { cout << "You turned, but there's no quarter\n"; }
    void dispense() override { cout << "You need to pay first\n"; }
    string toString() override { return "waiting for quarter"; }
};