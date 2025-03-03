#pragma once

#include <string>
using std::string;

#pragma region Pointer to Class Member
class Screen { //VERx1 (DO NOT USE IT EXCEPT FOR 19_04_x.cpp!)
public:
	typedef string::size_type pos;
	char get_cursor() const { return contents[cursor]; }
	char get() const;
	char get(pos ht, pos wd) const;
	string contents; //MINE
private:
	//ORIG string contents;
	pos cursor;
	pos height, width;
};
#pragma endregion
