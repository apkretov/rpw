#pragma once

#include <iostream>
using std::ostream;

#pragma region Writing a Variadic Function Template
template <typename T>
ostream &print(ostream &os, const T &t) { //TEST! //																												function to end the recursion and print the last element // this function must be declared before the variadic version of print is defined
	return os << t; // no separator after the last element in the pack
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest) { //TEST! //																							this version of print will be called for all but the last element in the pack
#ifndef  ORIG
	os << t << ", "; // print the first argument
#else //MINE
	os << "sizeof...(rest) = " << sizeof...(rest);
	os << "\tt = " << t << '\n';
#endif
	return print(os, rest...); //TEST! //																															recursive call; print the other arguments
}
#pragma endregion