#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "19_04.h"
using namespace std;

void Pointers_to_Data_Members() {
	const string Screen:: *pdata; //TEST!! //																												pdata can point to a string member of a const (or nonconst) Screen object
	pdata = &Screen::contents; //TEST!!

	{
		auto pdata = &Screen::contents; //TEST!
	}

#pragma region Using a Pointer to Data Member
	Screen myScreen, *pScreen = &myScreen;
	auto s = myScreen.*pdata; //TEST! //																												.* dereferences pdata to fetch the contents member from the object myScreen
	s = pScreen->*pdata; // ->* dereferences pdata to fetch contents from the object to which pScreen points
	cout << typeid(s).name() << '\n'; //MINE
#pragma endregion
 }

int main() {
	print_file_line();

	Pointers_to_Data_Members();

	return 0;
}
#endif