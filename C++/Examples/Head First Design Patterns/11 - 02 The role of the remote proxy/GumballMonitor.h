#pragma once

#include <iostream>
#include <memory>
#include "GumballMachine.h"

#pragma region Coding the Monitor
/* Java
public class GumballMonitor {
    GumballMachine machine; 
    public GumballMonitor(GumballMachine machine) { this.machine = machine; } // The monitor takes the machine in its constructor and assigns it to the machine instance variable.

    public void report() { // Our report method just prints a report with location, inventory and the machine's state.
        System.out.println("Gumball Machine: " + machine.getLocation());
        System.out.println("Current inventory: " + machine.getCount() + " gumballs");
        System.out.println("Current state: " + machine.getState());
    }
}
*/
class GumballMonitor {
    std::weak_ptr<GumballMachine> machine_; 
public:
    explicit GumballMonitor(std::shared_ptr<GumballMachine> machine) : machine_(machine) {} // The monitor takes the machine in its constructor and assigns it to the machine instance variable.

    void report() const { // Our report method just prints a report with location, inventory and the machine's state.
        if (auto machine = machine_.lock()) {
            std::cout << "std::Gumball Machine: " << machine->getLocation() << "\n";
            std::cout << "std::Current inventory: " << machine->getCount() << " gumballs\n";
            //ORIG std::cout << "std::Current state: " << machine->getState()->toString() << "\n"; //MINE: TO DO: This is a violation of the Principle of Least Knowledge. Delegate the toString() call through GumballMachine: string GumballMachine::getStateString() const { return state->toString(); }
            std::cout << "std::Current state: " << machine->getStateString() << "\n"; //MINE: By the Principle of Least Knowledge, delegate the toString() call through GumballMachine
        }
    }
};
#pragma endregion //Coding the Monitor