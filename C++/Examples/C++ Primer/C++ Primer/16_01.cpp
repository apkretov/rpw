#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef Defining_a_Template
int compare(const string &v1, const string &v2) { // returns 0 if the values are equal, -1 if v1 is smaller, 1 if v2 is smaller
	if (v1 < v2) 
		return -1;
	if (v2 < v1) 
		return 1;
	return 0;
}

int compare(const double &v1, const double &v2) {
	if (v1 < v2) 
		return -1;
	if (v2 < v1) 
		return 1;
	return 0;
}
#endif

int main(int argc, char argv[]) {
    print_file_line();

	//MINE
	string s1 = "abc";
	string s2 = "def";
	cout << compare(s1, s2) << '\n';
    double d1 = 1.23;
    double d2 = 4.56;
	cout << compare(d1, d2) << '\n';

	return 0;
}
#endif