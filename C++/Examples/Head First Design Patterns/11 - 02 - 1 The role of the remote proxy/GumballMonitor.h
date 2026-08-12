#pragma once

#include <memory>
#include <iostream>
#include "IGumballMachine.h"

#pragma region Trae
class GumballMonitor {
public:
	explicit GumballMonitor(std::shared_ptr<IGumballMachine> machine) : machine_(machine) {}

	void report() const {
		if (auto machine = machine_.lock()) {
			std::cout << "Gumball Machine: " << machine->getLocation() << "\n";
			std::cout << "Current inventory: " << machine->getCount() << " gumballs\n";
			std::cout << "Current state: " << machine->getStateString() << "\n";
		}
	}
private:
	std::weak_ptr<IGumballMachine> machine_;
};
#pragma endregion //Trae
