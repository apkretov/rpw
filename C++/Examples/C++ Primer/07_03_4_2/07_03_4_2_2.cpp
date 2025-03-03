#ifndef Making_A_Member_Function_A_Friend

#include <iostream>
#include "07_03_4_2_1.h"
using namespace std;

void Window_mgr::clear(ScreenIndex i) {
	try { //MINE 
		cout << "this = " << this << "\tWindow_mgr::clear(ScreenIndex i)...\n"; //MINE
		//ORIG Screen &s = screens[i]; // s is a reference to the Screen we want to clear
		Screen &s = screens.at(i); //MINE
		s.contents = string(s.height * s.width, ' '); // reset the contents of that Screen to all blanks
	} //MINE
	catch (const out_of_range &e) {
		cout << "this = " << this << "\tError: " << e.what() << '\n';
	}
}
#endif

Window_mgr::Window_mgr() : screens({Screen(24, 80, ' ')}) {} //TEST!!! // ch7/7.32.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch7/7.32.cpp