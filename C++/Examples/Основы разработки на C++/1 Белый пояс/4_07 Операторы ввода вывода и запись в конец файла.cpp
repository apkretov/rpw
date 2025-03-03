#if 0

#include <iostream>
#include <fstream>
#include "../../stdafx.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	ifstream input("4_06 - date.txt");
	int year;
	int month;
	int day;

	if (input) {
		input >> year;
		input.ignore(); //ORIG input.ignore(1); //TEST
		input >> month;
		input.ignore(); //ORIG input.ignore(1);
		input >> day;
		cout << year << ' ' << month << ' ' << day << '\n'; //MINE
	} else //MINE
		cout << "Error!\n";
}
#endif