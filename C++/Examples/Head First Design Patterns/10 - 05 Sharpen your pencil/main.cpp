#include <iostream>
#include "../../stdafx.h"
#include "vld.h"
#include "GumballMachine.h"
using std::cout;

int main() { 
	print_file_line();

	auto gumballMachine = GumballMachine::create(1);           
	cout << gumballMachine->toString();

	gumballMachine->insertQuarter();                                
	gumballMachine->turnCrank();

	cout << gumballMachine->toString();

	gumballMachine->refill(1);
	cout << gumballMachine->toString();

	return 0;
}
