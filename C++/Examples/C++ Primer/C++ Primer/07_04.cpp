#include "07_03_4.h"

#ifdef ON

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "RU");
    cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

#ifndef Class_Scope	
	Screen::pos ht = 24, wd = 80; //TEST! // use the pos type defined by Screen
	//ORIG Screen scr(ht, wd, ' ');
	Screen scr(ht, wd, 'A'); //MINE
	Screen *p = &scr;
	char c = scr.get(); // fetches the get member from the object scr
	c = p->get(); // fetches the get member from the object to which p points
	cout << c << '\n'; //MINE
#endif

	return 0;
}
#endif

#ifndef Scope_and_Members_Defined_Outside_the_Class

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s) { //TEST! // return type is seen before we’re in the scope of Window_mgr
	screens.push_back(s);
	return screens.size() - 1;
}
#endif