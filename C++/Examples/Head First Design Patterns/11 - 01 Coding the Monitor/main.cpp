#include <iostream>
#include "../../stdafx.h"
//OFF #include "vld.h"
#include "GumballMachine.h"
#include "GumballMonitor.h"
using std::cout;
using std::stoi;
using std::string;

#pragma region Testing the Monitor
/* Java
public class GumballMachineTestDrive {
	public static void main(String[] args) {
		int count = 0;

		if (args.length < 2) { // Pass in a location and initial # of gumballs on the command line.
			System.out.println("GumballMachine <name> <inventory>");
			System.exit(1);
		}

		count = Integer.parseInt(args[1]);
		GumballMachine gumballMachine = new GumballMachine(args[0], count); // Don't forget to give the constructor a location and count...

		GumballMonitor monitor = new GumballMonitor(gumballMachine); // ...and instantiate a monitor and pass it a machine to provide a report on.

		// rest of test code here

		monitor.report(); // When we need a report on the machine, we call the report() method.
	}
}
*/
int main(int argc, char *argv[]) {
	print_file_line();

	if (argc < 3) { // Pass in a location and initial # of gumballs on the command line.
		cout << "GumballMachine <name> <inventory>\n";
		return 1;
	}

	int count = stoi(argv[2]);
	auto gumballMachine = GumballMachine::create(argv[1], count); // Don't forget to give the constructor a location and count...

	GumballMonitor monitor(gumballMachine); // ...and instantiate a monitor and pass it a machine to provide a report on.

	// rest of test code here

	cout << "\nThe monitoring report\n"; //MINE
	monitor.report(); // When we need a report on the machine, we call the report() method.
	cout << '\n'; //MINE

	return 0;
}
#pragma endregion //Testing the Monitor
