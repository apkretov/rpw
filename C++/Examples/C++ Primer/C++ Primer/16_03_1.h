#pragma once

#include <iostream>
#include <sstream>
#include <string>
using std::string;
using std::ostringstream;

#pragma region Writing Overloaded Templates
template <typename T>
string debug_rep(const T &t) { // print any type we don’t otherwise handle
	ostringstream ret; // see § 8.3 (p. 321)
	ret << t; // uses T’s output operator to print a representation of t
	return ret.str(); // return a copy of the string to which ret is bound
}

template <typename T>
string debug_rep(T *p) { // print pointers as their pointer value, followed by the object to which the pointer points // NB: this function will not work properly with char*; see § 16.3 (p. 698)
	ostringstream ret;
	ret << "pointer: " << p; // print the pointer’s own value
	if (p)
		ret << " " << debug_rep(*p); // print the value to which p points
	else
		ret << " null pointer"; // or indicate that the p is null
	return ret.str(); // return a copy of the string to which ret is bound
}
#pragma endregion
