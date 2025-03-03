#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef Function_Matching_and_Overloaded_Operators
class SmallInt { //VER3
	friend SmallInt operator+(const SmallInt &, const SmallInt &);
public:
	SmallInt(int = 0); // conversion from int
	operator int() const { // conversion to int
		cout << "operator int()\n";
		return val;
	}
private:
	size_t val;
};

SmallInt::SmallInt(int i) : val(i) { //MINE
	cout << "Constructor\n";
}

SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs) { //MINE
	cout << "operator+(const SmallInt &, const SmallInt &)\n";
	return SmallInt();
}

void Function_Matching_and_Overloaded_Operators_() {
	cout << "SmallInt s1, s2:\n"; //MINE
	SmallInt s1, s2;
	
	cout << "\nSmallInt s3 = s1 + s2:\n"; //MINE
	SmallInt s3 = s1 + s2; // uses overloaded operator+
	//TEST! int i = s3 + 0; //																																										error: ambiguous
	
	//MINE
	cout << "\nint i = operator+(s3, 0):\n";
	int i = operator+(s3, 0); 

	//MINE
	cout << "\ni = s3 + SmallInt(0):\n";
	i = s3 + SmallInt(0);
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	
	Function_Matching_and_Overloaded_Operators_();

	return 0;
}
#endif