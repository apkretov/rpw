#ifdef ON

#include <iostream>
#include <regex>
#include "../../stdafx.h"
using namespace std;

void Using_Subexpressions() {
	regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase); // r has two subexpressions: the first is the part of the file name before the period // the second is the file extension
	smatch results;
	string filename;
	while (cin >> filename)
		if (regex_search(filename, results, r))
			cout << results.str(1) << endl; // print the first subexpression
}

bool valid(const smatch &m); //MINE

void Subexpressions_for_Data_Validation() {
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
	regex r(phone); // a regex to find our pattern
	smatch m;
#undef ORIG
#ifdef ORIG
	string s;
	while (getline(cin, s)) { // read each record from the input file
#else //MINE
	string s = "+1 (222) 333-4444";
#endif
		for (sregex_iterator it(s.begin(), s.end(), r), end_it; // for each matching phone number
			it != end_it; ++it)
			if (valid(*it)) // check whether the number’s formatting is valid
				cout << "valid: " << it->str() << endl;
			else
				cout << "not valid: " << it->str() << endl;
#ifdef ORIG
	}
#endif
}

#pragma region Using the Submatch Operations
bool valid(const smatch &m) {
	if (m[1].matched) // if there is an open parenthesis before the area code
		return m[3].matched // the area code must be followed by a close parenthesis // and followed immediately by the rest of the number or a space
		&& (m[4].matched == 0 || m[4].str() == " ");
	else
		return !m[3].matched // then there can’t be a close after the area code // the delimiters between the other two components must match
		&& m[4].str() == m[6].str();
}
#pragma endregion

int main() {
	print_file_line();

	//Using_Subexpressions();
	Subexpressions_for_Data_Validation();
}
#endif
