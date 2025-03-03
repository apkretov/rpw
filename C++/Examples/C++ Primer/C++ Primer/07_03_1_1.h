#pragma once

#include <string>
using std::string;

#ifdef Defining_a_Type_Member
class Screen__mutable_Data_Members { //VER1
public:
#ifdef _1
	typedef string::size_type pos; //TEST
#elif !_2
	using pos = string::size_type; //TEST // alternative way to declare a type member using a type alias
#endif
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;
};
#endif

#ifndef Member_Functions_of_Class_Screen
class Screen__Member_Functions_of_Class_Screen { //VER2
public:
	typedef string::size_type pos;
	Screen__Member_Functions_of_Class_Screen() = default; // needed because Screen has another constructor
	
	Screen__Member_Functions_of_Class_Screen(pos ht, pos wd, char c) : // cursor initialized to 0 by its in-class initializer
		height(ht), width(wd), contents(ht * wd, c) { 
	}
	
	char get() const { // get the character at the cursor // implicitly inline
		return contents[cursor];
	} 
	
	inline char get(pos ht, pos wd) const; // explicitly inline
	
	Screen__Member_Functions_of_Class_Screen &move(pos r, pos c); // can be made inline later
//ORIG private:
protected: //MINE
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;
};
#endif

#ifndef mutable_Data_Members
class Screen__mutable_Data_Members /*VER3*/ : public Screen__Member_Functions_of_Class_Screen { //MINE
public:
	Screen__mutable_Data_Members() = default; //MINE

	Screen__mutable_Data_Members(pos ht, pos wd, char c) : Screen__Member_Functions_of_Class_Screen(ht, wd, c) {} //MINE

	void some_member() const;
private:
	mutable size_t access_ctr{}; //TEST!!! //																																						may change even in a const object
	// other members as before
};
#endif
