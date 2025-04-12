#pragma once

#include <iostream>
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
using std::cout;

#pragma region Writing the code
/* Java
package headfirst.designpatterns.state.gumball;

public class GumballMachine {
	final static int SOLD_OUT = 0;
	final static int NO_QUARTER = 1;
	final static int HAS_QUARTER = 2;
	final static int SOLD = 3;
	int state = SOLD_OUT;
	int count = 0;
	public GumballMachine(int count) {
		this.count = count;
		if (count > 0) {
			state = NO_QUARTER;
		}
	}
	public void insertQuarter() {
		if (state == HAS_QUARTER) {
			System.out.println("You can't insert another quarter");
		} else if (state == NO_QUARTER) {
			state = HAS_QUARTER;
			System.out.println("You inserted a quarter");
		} else if (state == SOLD_OUT) {
			System.out.println("You can't insert a quarter, the machine is sold out");
		} else if (state == SOLD) {
			System.out.println("Please wait, we're already giving you a gumball");
		}
	}
	public void ejectQuarter() {
		if (state == HAS_QUARTER) {
			System.out.println("Quarter returned");
			state = NO_QUARTER;
		} else if (state == NO_QUARTER) {
			System.out.println("You haven't inserted a quarter");
		} else if (state == SOLD) {
			System.out.println("Sorry, you already turned the crank");
		} else if (state == SOLD_OUT) {
			System.out.println("You can't eject, you haven't inserted a quarter yet");
		}
	}
	public void turnCrank() {
		if (state == SOLD) {
			System.out.println("Turning twice doesn't get you another gumball!");
		} else if (state == NO_QUARTER) {
			System.out.println("You turned but there's no quarter");
		} else if (state == SOLD_OUT) {
			System.out.println("You turned, but there are no gumballs");
		} else if (state == HAS_QUARTER) {
			System.out.println("You turned...");
			state = SOLD;
			dispense();
		}
	}
	private void dispense() {
		if (state == SOLD) {
			System.out.println("A gumball comes rolling out the slot");
			count = count - 1;
			if (count == 0) {
				System.out.println("Oops, out of gumballs!");
				state = SOLD_OUT;
			} else {
				state = NO_QUARTER;
			}
		} else if (state == NO_QUARTER) {
			System.out.println("You need to pay first");
		} else if (state == SOLD_OUT) {
			System.out.println("No gumball dispensed");
		} else if (state == HAS_QUARTER) {
			System.out.println("No gumball dispensed");
		}
	}
	public void refill(int numGumBalls) {
		this.count = numGumBalls;
		state = NO_QUARTER;
	}
	public String toString() {
		StringBuffer result = new StringBuffer();
		result.append("\nMighty Gumball, Inc.");
		result.append("\nJava-enabled Standing Gumball Model #2004\n");
		result.append("Inventory: " + count + " gumball");
		if (count != 1) {
			result.append("s");
		}
		result.append("\nMachine is ");
		if (state == SOLD_OUT) {
			result.append("sold out");
		} else if (state == NO_QUARTER) {
			result.append("waiting for quarter");
		} else if (state == HAS_QUARTER) {
			result.append("waiting for turn of crank");
		} else if (state == SOLD) {
			result.append("delivering a gumball");
		}
		result.append("\n");
		return result.toString();
	}
}
*/
class GumballMachine {
	static constexpr int SOLD_OUT = 0;
	static constexpr int NO_QUARTER = 1;
	static constexpr int HAS_QUARTER = 2;
	static constexpr int SOLD = 3;
	int state = SOLD_OUT;
	int count = 0;

public:
	GumballMachine(int count) { this->count = count; if (count > 0) state = NO_QUARTER; }
	void insertQuarter() {
		if (state == HAS_QUARTER)
			cout << "You can't insert another quarter\n";
		else if (state == NO_QUARTER) {
			state = HAS_QUARTER;
			cout << "You inserted a quarter\n";
		} else if (state == SOLD_OUT)
			cout << "You can't insert a quarter, the machine is sold out\n";
		else if (state == SOLD)
			cout << "Please wait, we're already giving you a gumball\n";
	}
	void ejectQuarter() {
		if (state == HAS_QUARTER) {
			cout << "Quarter returned\n";
			state = NO_QUARTER;
		} else if (state == NO_QUARTER)
			cout << "You haven't inserted a quarter\n";
		else if (state == SOLD)
			cout << "Sorry, you already turned the crank\n";
		else if (state == SOLD_OUT)
			cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	void turnCrank() {
		if (state == SOLD)
			cout << "Turning twice doesn't get you another gumball!\n";
		else if (state == NO_QUARTER)
			cout << "You turned but there's no quarter\n";
		else if (state == SOLD_OUT)
			cout << "You turned, but there are no gumballs\n";
		else if (state == HAS_QUARTER) {
			cout << "You turned...\n";
			state = SOLD;
			dispense();
		}
	}
	void refill(int numGumBalls) { count = numGumBalls; state = NO_QUARTER; }
	string toString() {
		stringstream result;
		result << "\nMighty Gumball, Inc.";
		result << "\nC++-enabled Standing Gumball Model #2004\n";
		result << "Inventory: " << count << " gumball";
		if (count != 1) result << "s";
		result << "\nMachine is ";
		if (state == SOLD_OUT) result << "sold out";
		else if (state == NO_QUARTER) result << "waiting for quarter";
		else if (state == HAS_QUARTER) result << "waiting for turn of crank";
		else if (state == SOLD) result << "delivering a gumball";
		result << "\n";
		return result.str();
	}

	void dispense() {
		if (state == SOLD) {
			cout << "A gumball comes rolling out the slot\n";
			count = count - 1;
			if (count == 0) {
				cout << "Oops, out of gumballs!\n";
				state = SOLD_OUT;
			} else
				state = NO_QUARTER;
		} else if (state == NO_QUARTER)
			cout << "You need to pay first\n";
		else if (state == SOLD_OUT)
			cout << "No gumball dispensed\n";
		else if (state == HAS_QUARTER)
			cout << "No gumball dispensed\n";
	}
};
#pragma endregion //Writing the code