#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "12_01_6_3.h"
#include "14_07.h"
using namespace std;

void Member_Access_Operators() {
	StrBlob a1 = {"hi", "bye", "now"};
	StrBlobPtr p(a1); // p points to the vector inside a1
	*p = "okay"; // assigns to the first element in a1
	cout << p->size() << endl; // prints 4, the size of the first element in a1
	cout << (*p).size() << endl; // equivalent to p->size()
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	Member_Access_Operators();

	return 0;
}
#endif