#pragma once

#include <iostream>
#include <memory>
#include "GumballMachine.h"
using std::cout;
using std::shared_ptr;
using std::string;
using std::weak_ptr;

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
    weak_ptr<GumballMachine> machine_; 
public:
    explicit GumballMonitor(shared_ptr<GumballMachine> machine) : machine_(machine) {} // The monitor takes the machine in its constructor and assigns it to the machine instance variable.

    void report() const { // Our report method just prints a report with location, inventory and the machine's state.
        if (auto machine = machine_.lock()) {
            cout << "Gumball Machine: " << machine->getLocation() << "\n";
            cout << "Current inventory: " << machine->getCount() << " gumballs\n";
            cout << "Current state: " << machine->getState()->toString() << "\n"; //MINE: TO DO: This is a violation of the Principle of Least Knowledge. Delegate the toString() call through GumballMachine: string GumballMachine::getStateString() const { return state->toString(); }
        }
    }
};
#pragma endregion //Coding the Monitor