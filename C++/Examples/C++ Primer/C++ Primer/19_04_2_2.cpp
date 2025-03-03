#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Pointer to Class Member
class Screen { //VERx3 (DO NOT USE IT EXCEPT FOR 19_04_2_2.cpp!)
public:
	typedef string::size_type pos;
	char get_cursor() const { return contents[cursor]; }
	char get() const;
	char get(pos ht, pos wd) const;
#pragma region A Function Returning a Pointer to Data Member
	static const string Screen:: *data() { //TEST! //																									data is a static member that returns a pointer to member
		return &Screen::contents;
	} // other members as before
#pragma endregion
#pragma region Pointer-to-Member Function Tables // other interface and implementation members as before
	Screen &home(); //TEST! //																															cursor movement functions
	Screen &forward();
	Screen &back();
	Screen &up();
	Screen &down();
	// other interface and implementation members as before
	using Action = Screen & (Screen:: *)(); //TEST! //																									Action is a pointer that can be assigned any of the cursor movement members
	enum Directions { HOME, FORWARD, BACK, UP, DOWN }; //TEST //																						specify which direction to move; enum see § 19.3 (p. 832)
	Screen &move(Directions);
private:
	static Action Menu[]; //TEST! //																													function table
#pragma endregion
private:
	string contents;
	pos cursor;
	pos height, width;
};

Screen &Screen::move(Directions cm) { // run the element indexed by cm on this object
	return (this->*Menu[cm])(); //TEST! //																												Menu[cm] points to a member function
}

Screen::Action Screen::Menu[] = {&Screen::home, &Screen::forward, &Screen::back, &Screen::up, &Screen::down,};

void Pointer_to_Member_Function_Tables() {
	Screen myScreen;
	myScreen.move(Screen::HOME); // invokes myScreen.home
	myScreen.move(Screen::DOWN); // invokes myScreen.down
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif