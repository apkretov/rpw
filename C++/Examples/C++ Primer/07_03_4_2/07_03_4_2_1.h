#pragma once

#include <string>
#include <iostream>
using namespace std;
#include "07_03_4_2_2.h"

#ifndef Defining_a_Type_Member
class Screen { //VER7
#ifndef Making_A_Member_Function_A_Friend
	friend void Window_mgr::clear(ScreenIndex); //TEST!! //																										Window_mgr::clear must have been declared before class Screen
#endif
public:
#ifdef _1
	typedef string::size_type pos;
#elif !_2
	using pos = string::size_type; // alternative way to declare a type member using a type alias
#endif
#ifndef Member_Functions_of_Class_Screen
	Screen() = default; // needed because Screen has another constructor
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht *wd, c) {} // cursor initialized to 0 by its in-class initializer

	char get() const { // get the character at the cursor // implicitly inline
		return contents[cursor];
	}

	inline char get(pos ht, pos wd) const; // explicitly inline
	Screen &move(pos r, pos c); // can be made inline later
#endif
#ifndef mutable_Data_Members
	void some_member() const;
#endif
#ifndef Functions_That_Return_this
	Screen &set(char);
	Screen &set(pos, pos, char);
#endif
#ifndef Overloading_Based_on_const
	Screen &display(ostream &os) { // display overloaded on whether the object is const or not
		do_display(os); 
		return *this;
	}

	const Screen &display(ostream &os) const {
		do_display(os); 
		return *this;
	}
#endif

private:
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;
#ifndef mutable_Data_Members
	mutable size_t access_ctr{}; //	may change even in a const object
#endif
#ifndef Overloading_Based_on_const
	void do_display(ostream &os) const { // function to do the work of displaying a Screen
		os << contents; 
	} 
#endif
};
#endif
