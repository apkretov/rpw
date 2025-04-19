#pragma once
#include <iostream>
#include "State.h"
#include "GumballMachine.h"
#include <memory>

#pragma region Sharpen your pencil
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumball
public class SoldOutState implements State {
	GumballMachine gumballMachine;
	public SoldOutState(GumballMachine gumballMachine) { this.gumballMachine = gumballMachine; }
	public void insertQuarter() { System.out.println("You can't insert a quarter, the machine is sold out"); }
	public void ejectQuarter() { System.out.println("You can't eject, you haven't inserted a quarter yet"); }
	public void turnCrank() { System.out.println("You turned, but there are no gumballs"); }
	public void dispense() { System.out.println("No gumball dispensed"); }
	public String toString() { return "sold out"; }
}
*/
class SoldOutState : public State {
	GumballMachine* gumballMachine;
public:
	SoldOutState(GumballMachine* gumballMachine) : gumballMachine(gumballMachine) {}
	void insertQuarter() override {
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void ejectQuarter() override { std::cout << "You can't eject, you haven't inserted a quarter yet\n"; }
	void turnCrank() override { std::cout << "You turned, but there are no gumballs\n"; }
	void dispense() override { std::cout << "No gumball dispensed\n"; }
	std::string toString() override { return "sold out"; }
};
#pragma endregion //Sharpen your pencil
