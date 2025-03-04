#include "stdafx.h" 
#include <iostream>
#include <string>
using namespace std;

int main () {
	cout << "Enter an interger value i: ";
	int i;
	cin >> i;
	cout << "i = " << i << endl;
	string mystr; // cin with strings @ http://www.cplusplus.com/doc/tutorial/basic_io/
	cout << "What's your name? ";
	getline (cin, mystr);
	cout << "Hello " << mystr << ".\n";
	cout << "What is your favorite team? ";
	getline (cin, mystr);
	cout << "I like " << mystr << " too!\n";
	return 0;
}