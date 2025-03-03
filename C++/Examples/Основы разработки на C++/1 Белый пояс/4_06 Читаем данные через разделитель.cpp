#if 0

#include <iostream>
#include <fstream>
#include "../../stdafx.h"
using namespace std;

int main() {
	PRINT_FILE_LINE();

	ifstream input("4_06 - date.txt");
	string year;
	string month;
	string day;

	if (input) {
		getline(input, year, '-');
		getline(input, month, '-');
		getline(input, day, '-');
		cout << year << ' ' << month << ' ' << day << '\n'; //MINE
	} else //MINE
		cout << "Error!\n";
}
#endif