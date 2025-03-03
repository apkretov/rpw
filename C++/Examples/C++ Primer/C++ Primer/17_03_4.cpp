#ifdef ON

#include <array>
#include <iostream>
#include <ranges>
#include <regex>
#include "../../stdafx.h"

#pragma region Flags to Control Matches and Formatting
using std::regex_constants::format_no_copy;
#pragma endregion

using namespace std;

void Using_regex_replace() {
	string fmt = "$2.$5.$7"; // reformat numbers to ddd.ddd.dddd
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})"; //MINE
	regex r(phone); // a regex to find our pattern
	string number = "(908) 555-0132";
	cout << number << " converted to:\n"; //MINE
	cout << regex_replace(number, r, fmt) << endl;
}


#pragma region Replacing Only Part of the Input Sequence
string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
regex r(phone); // a regex to find our pattern
smatch m;
string fmt = "$2.$5.$7"; // reformat numbers to ddd.ddd.dddd

void Replacing_Only_Part_of_the_Input_Sequence() {
	//string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	//regex r(phone); // a regex to find our pattern
	//smatch m;
	//string fmt = "$2.$5.$7"; // reformat numbers to ddd.ddd.dddd

#undef ORIG
#ifdef ORIG
	string s;
	while (getline(cin, s)) // read each record from the input file
#else //MINE //ERR: No replacement in my example. For replacement see the original version.
	array<string, 3> file =
	{"morgan(201) 555 - 0168 862 - 555 - 0123",
	"drew(973)555.0130",
	"lee(609) 555 - 0132 2015550175 800.555 - 0100"};
	ranges::copy(file, ostream_iterator<string>(cout, "\n"));
	cout << '\n';
	for (const auto &s : file)
#endif
		cout << regex_replace(s, r, fmt) << endl;
}
#pragma endregion

void Using_Format_Flags() {
	string fmt2 = "$2.$5.$7 "; // generate just the phone numbers: use a new format string // put space after the last number as a separator 
#undef ORIG
#ifdef ORIG
	string s;
	while (getline(cin, s)) // read each record from the input file
#else //MINE
	array<string, 3> file =
	{"morgan(201) 555 - 0168 862 - 555 - 0123",
	"drew(973)555.0130",
	"lee(609) 555 - 0132 2015550175 800.555 - 0100"};
	ranges::copy(file, ostream_iterator<string>(cout, "\n"));
	cout << '\n';
	for (const auto &s : file)
#endif
	cout << regex_replace(s, r, fmt2, format_no_copy) << endl; // tell regex_replace to copy only the text that it replaces
}

int main() {
	print_file_line();

	//Using_regex_replace();
	//Replacing_Only_Part_of_the_Input_Sequence();	
	Using_Format_Flags();
}
#endif
