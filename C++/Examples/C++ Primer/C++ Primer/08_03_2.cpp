#ifdef ON

#include <iostream>
#include <sstream>
#include "08_03_1.h"
using namespace std;

constexpr bool valid(const string &s) { //MINE
	return false;
}

const string &format(const string &s) { //MINE
	return s;
}

void Using_ostringstreams() {
	vector<PersonInfo> people; // will hold all the records from the input
	Using_an_istringstream(people); //MINE

	for (const auto &entry : people) { // for each entry in people
		ostringstream formatted, badNums; // objects created on each loop

		for (const auto &nums : entry.phones) { // for each number
			if (!valid(nums)) {
				badNums << " " << nums; // string in badNums
			} else
				formatted << " " << format(nums); // ‘‘writes’’ to formatted’s string
		}
		if (badNums.str().empty()) // there were no bad numbers
			//ORIG os << entry.name << " " // print the name
			cout << entry.name << " " //MINE
			<< formatted.str() << endl; // and reformatted numbers
		else // otherwise, print the name and bad numbers
			cerr << "input error: " << entry.name
			<< " invalid number(s) " << badNums.str() << endl;
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Using_ostringstreams();

	return 0;
}
#endif
