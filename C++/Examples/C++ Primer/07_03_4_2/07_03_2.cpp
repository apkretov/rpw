#include "07_03_4_2_1.h"

#ifndef Functions_That_Return_this
inline Screen &Screen::set(char c) {
	contents[cursor] = c; // set the new value at the current cursor location
	return *this; // return this object as an lvalue
}

inline Screen &Screen::set(pos r, pos col, char ch) {
	contents[r * width + col] = ch; // set specified location to given value
	return *this; // return this object as an lvalue
}

inline Screen &Screen::move(pos r, pos c) { //MINE
	Screen::move(r, c);
	return *this;
}
#endif