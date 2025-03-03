#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "19_04.h"
using namespace std;

void Pointers_to_Member_Functions() {
	auto pmf = &Screen::get_cursor; //TEST! //																											pmf is a pointer that can point to a Screen member function that is const // that returns a char and takes no arguments

	char (Screen:: * pmf2)(Screen::pos, Screen::pos) const; //TEST!
	pmf2 = &Screen::get;

	//TEST char Screen:: *p(Screen::pos, Screen::pos) const; //																							error: nonmember function p cannot have a const qualifier

	// pmf points to a Screen member that takes no arguments and returns char
	pmf = &Screen::get; //TEST! //																														must explicitly use the address-of operator
	//TEST! pmf = Screen::get; //																														error: no conversion to pointer for member functions

#pragma region Using a Pointer to Member Function
	Screen myScreen, *pScreen = &myScreen;
	char c1 = (pScreen->*pmf)(); //TEST //																												call the function to which pmf points on the object to which pScreen points
	char c2 = (myScreen.*pmf2)(0, 0); //TEST //																											passes the arguments 0, 0 to the two-parameter version of get on the object myScreen
#pragma endregion
}

void Using_Type_Aliases_for_Member_Pointers() {
	using Action = char (Screen:: *)(Screen::pos, Screen::pos) const; //TEST //																			Action is a type that can point to a member function of Screen // that returns a char and takes two pos arguments
	Action get = &Screen::get; // get points to the get member of Screen

	Screen &action(Screen &, Action = &Screen::get); //TEST! //																							action takes a reference to a Screen and a pointer to a Screen member function

	Screen myScreen;
	// equivalent calls:
	action(myScreen); //TEST //																															uses the default argument
	action(myScreen, get); //TEST //																													uses the variable get that we previously defined
	action(myScreen, &Screen::get); //TEST //																											passes the address explicitly
}

int main() {
	print_file_line();

	Pointers_to_Member_Functions();

	return 0;
}
#endif