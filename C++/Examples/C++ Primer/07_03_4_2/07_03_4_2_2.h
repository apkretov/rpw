#pragma once

#include <string>
#include <vector>
using namespace std;

#ifndef Making_A_Member_Function_A_Friend
class Screen;

class Window_mgr {
public:
	using ScreenIndex = vector<Screen>::size_type; // location ID for each screen on the window
	Window_mgr(); //MINE
	void clear(ScreenIndex); // reset the Screen at the given position to all blanks
private:
	//ORIG vector<Screen> screens{Screen(24, 80, ' ')}; 
	vector<Screen> screens; //MINE 
};
#endif
