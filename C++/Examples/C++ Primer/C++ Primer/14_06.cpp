#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "12_01_6_3.h"
#include "14_06_1.h"
using namespace std;

void Calling_the_Postfix_Operators_Explicitly() {
	StrBlob a1 = {"aaa", "bbb", "ccc"}; //MINE
	print(a1); //MINE

	StrBlobPtr p(a1); // p points to the vector inside a1
	p.operator++(0); // call postfix operator++
	p.operator++(); // call prefix operator++

	cout << (p--).deref() << '\n'; //MINE
	cout << (++p).deref() << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	Calling_the_Postfix_Operators_Explicitly();

	return 0;
}
#endif