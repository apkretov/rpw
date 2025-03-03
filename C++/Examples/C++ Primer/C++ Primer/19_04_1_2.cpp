#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region A Function Returning a Pointer to Data Member
#pragma region Pointer to Class Member
class Screen { //VERx2 (DO NOT USE IT EXCEPT FOR 19_04_1_2.cpp!)
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
private:
	string contents;
	pos cursor;
	pos height, width;
};
#pragma endregion

void A_Function_Returning_a_Pointer_to_Data_Member() {
	const string Screen:: *pdata = Screen::data(); //TEST! //																							data() returns a pointer to the contents member of class Screen
	auto p = Screen::data(); //MINE

	Screen myScreen; //MINE
	auto s = myScreen.*pdata; //TEST! //																												fetch the contents of the object named myScreen
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif