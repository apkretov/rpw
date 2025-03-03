#include <iostream>
#include <exception>
#include "07_03_4_2_1.h"
using namespace std;

#ifndef Making_Members_inline
char Screen::get(pos r, pos c) const { // declared as inline in the class
	pos row = r * width; // compute row location
	//ORIG return contents[row + c]; // return character at the given column
	try { //MINE
		return contents.at(row + c); // return character at the given column
	}
	catch (const out_of_range &e) { //MINE
		cerr << "Error: " << e.what() << "\tFile: " << __FILE__ << "\tLine: " << __LINE__ << endl;
	}
}
#endif

#ifndef mutable_Data_Members
void Screen::some_member() const {
	++access_ctr; // keep a count of the calls to any member function
	// whatever other work this member needs to do
}
#endif

#ifndef Member_Functions_of_Class_Screen
inline // we can specify inline on the definition
Screen &Screen::move(pos r, pos c) {
	pos row = r * width; // compute the row location
	cursor = row + c; // move cursor to the column within that row
	return *this; // return this object as an lvalue
}
#endif
