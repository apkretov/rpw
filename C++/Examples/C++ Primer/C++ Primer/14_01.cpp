#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

void Basic_Concepts() {
	//TEST! int operator+(int, int); //																																								error: cannot redefine the built-in operator for ints
}

struct d { //MINE
	int i{};
	
	friend static int operator+(const d &lhs, const d &rhs) {
		return lhs.i + rhs.i;
	}

	int operator+=(const d &rhs) {
		i += rhs.i;
		return i;
	}
};

void Calling_an_Overloaded_Operator_Function_Directly() {
	d data1{111}, data2{222}; //MINE
	
	//																																																equivalent calls to a nonmember operator function
	data1 + data2; //TEST! //																																										normal expression
	operator+(data1, data2); //TEST! //																																								equivalent function call

	data1 += data2; //																																												expression-based ‘‘call’’
	data1.operator+=(data2); //																																										equivalent call to a member operator function
}

void Choosing_Member_or_Nonmember_Implementation() {
	string s = "world";
	string t = s + "!"; // ok: we can add a const char* to a string
	string u = "hi" + s; // would be an error if + were a member of string
}

int main(int argc, char *argv[]) {
	print_file_line();

	Calling_an_Overloaded_Operator_Function_Directly();

	return 0;
}
#endif