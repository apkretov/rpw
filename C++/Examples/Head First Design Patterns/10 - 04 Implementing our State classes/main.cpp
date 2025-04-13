#include <iostream>
#include "../../stdafx.h"
#include "vld.h"
#include "GumballMachine.h"
using std::cout;

/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/state/gumball
public class GumballMachineTestDrive {
    public static void main(String[] args) {
        GumballMachine gumballMachine = new GumballMachine(5);
        System.out.println(gumballMachine);
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);
        gumballMachine.insertQuarter();
        gumballMachine.ejectQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        gumballMachine.ejectQuarter();
        System.out.println(gumballMachine);
        gumballMachine.insertQuarter();
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        gumballMachine.insertQuarter();
        gumballMachine.turnCrank();
        System.out.println(gumballMachine);
    }
}
*/
int main() {
	print_file_line();

	auto gumballMachine = GumballMachine::create(5);
	cout << gumballMachine->toString();

	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();

	cout << gumballMachine->toString();

	gumballMachine->insertQuarter();
	gumballMachine->ejectQuarter();
	gumballMachine->turnCrank();

	cout << gumballMachine->toString();

	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->ejectQuarter();

	cout << gumballMachine->toString();

	gumballMachine->insertQuarter();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();

	cout << gumballMachine->toString();

	return 0;
}