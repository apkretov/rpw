#pragma once

#include "07_03_1_1.h"

#ifndef Functions_That_Return_this
class Screen__Functions_That_Return_this /*VER4*/ : public Screen__mutable_Data_Members { //MINE
public:
	Screen__Functions_That_Return_this() = default;
	Screen__Functions_That_Return_this(pos ht, pos wd, char c) : Screen__mutable_Data_Members(ht, wd, c) {}
	Screen__Functions_That_Return_this &set(char);
	Screen__Functions_That_Return_this &set(pos, pos, char);
	// other members as before
	Screen__Functions_That_Return_this &move(pos r, pos c); //MINE
};
#endif

#ifndef Overloading_Based_on_const

#include <iostream>

class Screen__Overloading_Based_on_const /*VER5*/ : public Screen__Functions_That_Return_this {
public:
	Screen__Overloading_Based_on_const() = default; //MINE
	Screen__Overloading_Based_on_const(pos ht, pos wd, char c) : Screen__Functions_That_Return_this(ht, wd, c) {} //MINE

	Screen__Overloading_Based_on_const &display(std::ostream &os) { // display overloaded on whether the object is const or not
		do_display(os); return *this;
	}
	
	const Screen__Overloading_Based_on_const &display(std::ostream &os) const {
		do_display(os); return *this;
	}

	Screen__Overloading_Based_on_const &set(pos ht, pos wd, char c) { //MINE
		Screen__Functions_That_Return_this::set(ht, wd, c);
		return *this;
	}

	Screen__Overloading_Based_on_const &set(char c) { //MINE
		Screen__Functions_That_Return_this::set(c);
		return *this;
	}

private:
	void do_display(std::ostream &os) const { os << contents; } // function to do the work of displaying a Screen
	// other members as before
};
#endif
