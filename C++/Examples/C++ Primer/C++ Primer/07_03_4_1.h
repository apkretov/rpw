#pragma once

#include "07_03_2.h"

#ifndef Friendship_Between_Classes
class Screen__Friendship_Between_Classes /*VER6*/ : public Screen__Overloading_Based_on_const {
	friend class Window_mgr__Friendship_Between_Classes; //TEST // Window_mgr members can access the private parts of class Screen
	// . . . rest of the Screen class
public:
	Screen__Friendship_Between_Classes() = default; //MINE
	
	//Screen__Friendship_Between_Classes(pos ht, pos wd, char c) { //MINE
	//	Screen__Overloading_Based_on_const(ht, wd, c);
	//}
	Screen__Friendship_Between_Classes(pos ht, pos wd, char c) : Screen__Overloading_Based_on_const(ht, wd, c) {} //MINE
};
#endif
