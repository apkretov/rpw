#pragma once

#include <iostream>
#include "GumballMachineI.h"

#pragma region Trae
class GumballMonitor {
	const IGumballMachine &machine;
public:
	explicit GumballMonitor(const IGumballMachine &machine) : machine(machine) {}

	void report() const {
		using std::cout;
		cout << "Gumball Machine: " << machine.getLocation() << "\n";
		cout << "Current inventory: " << machine.getCount() << " gumballs\n";
		cout << "Current state: " << machine.getStateString() << "\n";
	}
};
#pragma endregion //Trae
