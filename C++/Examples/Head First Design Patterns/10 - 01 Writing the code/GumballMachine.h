#pragma once

#include <string>
#include <memory>
#include "State.h"
using std::string;
using std::to_string;
using std::shared_ptr;

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumball
public class GumballMachine {
    private State soldOutState;
    private State noQuarterState;
    private State hasQuarterState;
    private State soldState;
    private State state;
    private int count = 0;
    public GumballMachine(int numberGumballs) {
        soldOutState = new SoldOutState(this);
        noQuarterState = new NoQuarterState(this);
        hasQuarterState = new HasQuarterState(this);
        soldState = new SoldState(this);
        this.count = numberGumballs;
        if (numberGumballs > 0) state = noQuarterState;
        else state = soldOutState;
    }
    public void insertQuarter() { state.insertQuarter(); }
    public void ejectQuarter() { state.ejectQuarter(); }
    public void turnCrank() {
        state.turnCrank();
        state.dispense();
    }
    void setState(State state) { this.state = state; }
    void releaseBall() {
        if (count > 0) count = count - 1;
    }
    public State getState() { return state; }
    public State getSoldOutState() { return soldOutState; }
    public State getNoQuarterState() { return noQuarterState; }
    public State getHasQuarterState() { return hasQuarterState; }
    public State getSoldState() { return soldState; }
    public int getCount() { return count; }
    public String toString() {
        StringBuffer result = new StringBuffer();
        result.append("\nMighty Gumball, Inc.");
        result.append("\nJava-enabled Standing Gumball Model #2004");
        result.append("\nInventory: " + count + " gumball");
        if (count != 1) result.append("s");
        result.append("\n");
        result.append("Machine is " + state + "\n");
        return result.toString();
    }
}
*/

class State;

class GumballMachine : public std::enable_shared_from_this<GumballMachine> {
    shared_ptr<State> soldOutState;
    shared_ptr<State> noQuarterState;
    shared_ptr<State> hasQuarterState;
    shared_ptr<State> soldState;
    shared_ptr<State> state;
    int count;
public:
    static shared_ptr<GumballMachine> create(int numberGumballs);
private:
    GumballMachine(int numberGumballs);
    void initialize();
public:
    void insertQuarter() { state->insertQuarter(); }
    void ejectQuarter() { state->ejectQuarter(); }

    void turnCrank() {
        state->turnCrank();
        state->dispense();
    }
    
	void setState(shared_ptr<State> state) { this->state = state; }
    void releaseBall() { if (count > 0) count = count - 1; }
    shared_ptr<State> getState() { return state; }
    shared_ptr<State> getSoldOutState() { return soldOutState; }
    shared_ptr<State> getNoQuarterState() { return noQuarterState; }
    shared_ptr<State> getHasQuarterState() { return hasQuarterState; }
    shared_ptr<State> getSoldState() { return soldState; }
    int getCount() { return count; }

    string toString() {
        string result;
        result += "\nMighty Gumball, Inc.";
        result += "\nC++-enabled Standing Gumball Model #2004";
        result += "\nInventory: " + to_string(count) + " gumball";
        if (count != 1) 
			result += "s";
        result += "\n";
        result += "Machine is " + state->toString() + "\n";
        return result;
    }
};