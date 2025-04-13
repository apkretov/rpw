#include <iostream>
#include "../../stdafx.h"
//#include "vld.h"
#include "GumballMachine.h"
using std::cout;

#pragma region Demo for the CEO of Mighty Gumball, Inc.
/* Java
public class GumballMachineTestDrive { // This code really hasn't changed at all; we just shortened it a bit.
	public static void main(String[] args) {
		GumballMachine gumballMachine = new GumballMachine(5); // Once, again, start with a gumball machine with 5 gumballs.

		System.out.println(gumballMachine);

		gumballMachine.insertQuarter(); // We want to get a winning state, so we just keep pumping in those quarters and turning the crank. We print out the state of the gumball machine every so often...
		gumballMachine.turnCrank();

		System.out.println(gumballMachine);

		gumballMachine.insertQuarter();
		gumballMachine.turnCrank();
		gumballMachine.insertQuarter();
		gumballMachine.turnCrank();

		System.out.println(gumballMachine);
	}
}
*/
int main() { // This code really hasn't changed at all; we just shortened it a bit.
	print_file_line();

	auto gumballMachine = GumballMachine::create(5); // Once, again, start with a gumball machine with 5 gumballs.
	cout << gumballMachine->toString();

	gumballMachine->insertQuarter(); // We want to get a winning state, so we just keep pumping in those quarters and turning the crank. We print out the state of the gumball machine every so often...
	gumballMachine->turnCrank();

	cout << gumballMachine->toString();

	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();

	cout << gumballMachine->toString();

	return 0;
}
#pragma endregion //Demo for the CEO of Mighty Gumball, Inc.