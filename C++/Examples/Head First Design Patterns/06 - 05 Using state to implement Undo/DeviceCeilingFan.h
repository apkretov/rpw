#pragma once

#include <iostream>
#include <string>
#include <string_view>
using std::cout;
using std::string;
using std::string_view;

#pragma region Using state to implement Undo
/* Java
public class CeilingFan {
	public static final int HIGH = 3;
	public static final int MEDIUM = 2;
	public static final int LOW = 1;
	public static final int OFF = 0;
	String location;
	int speed; // Notice that the CeilingFan class holds local state representing the speed of the ceiling fan.

	public CeilingFan(String location) {
		this.location = location;
		speed = OFF;
	}

	public void high() { // These methods set the speed of the ceiling fan.
		speed = HIGH;
		// code to set fan to high
	}

	public void medium() {
		speed = MEDIUM;
		// code to set fan to medium
	}

	public void low() {
		speed = LOW;
		// code to set fan to low
	}

	public void off() {
		speed = OFF;
		// code to turn fan off
	}

	public int getSpeed() { return speed; } // We can get the current speed of the ceiling fan using getSpeed().
}
*/
class CeilingFan {
public:
    string location_;
    int speed_; // Notice that the CeilingFan class holds local state representing the speed of the ceiling fan.
public:
    static const int HIGH = 3;
    static const int MEDIUM = 2;
    static const int LOW = 1;
    static const int OFF = 0;

	explicit CeilingFan(string_view location) : location_(location), speed_(OFF) {}

    void high() { // These methods set the speed of the ceiling fan.
        speed_ = HIGH;
        cout << location_ << " ceiling fan is on high\n";
    }

    void medium() {
        speed_ = MEDIUM;
        cout << location_ << " ceiling fan is on medium\n";
    }

    void low() {
        speed_ = LOW;
        cout << location_ << " ceiling fan is on low\n";
    }

    void off() {
        speed_ = OFF;
        cout << location_ << " ceiling fan is off\n";
    }

    int getSpeed() const { return speed_; } // We can get the current speed of the ceiling fan using getSpeed().
};
#pragma endregion //Using state to implement Undo
