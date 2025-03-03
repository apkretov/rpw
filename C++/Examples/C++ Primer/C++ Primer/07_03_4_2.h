#pragma once

#include <string>
#include <vector>
#include <exception>
#include "07_03_4_1.h"

#ifndef Friendship_Between_Classes
class Window_mgr__Friendship_Between_Classes {
public:
	using ScreenIndex = std::vector<Screen__Friendship_Between_Classes>::size_type; // location ID for each screen on the window
	void clear(ScreenIndex); // reset the Screen at the given position to all blanks
private:
	std::vector<Screen__Friendship_Between_Classes> screens{Screen__Friendship_Between_Classes(24, 80, ' ')};
};
void Window_mgr__Friendship_Between_Classes::clear(ScreenIndex i) {
	try { //MINE
		//ORIG Screen__Friendship_Between_Classes &s = screens[i]; // s is a reference to the Screen we want to clear
		Screen__Friendship_Between_Classes &s = screens.at(i); //MINE // s is a reference to the Screen we want to clear
		s.contents = std::string(s.height * s.width, ' '); // reset the contents of that Screen to all blanks
	} //MINE
	catch (const std::out_of_range &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
#endif