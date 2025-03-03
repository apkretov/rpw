#ifdef ON

#include <iostream>
#include <regex>
#include "../../stdafx.h"
using namespace std;

void Using_the_Regular_Expression_Library() {
	string pattern("[^c]ei"); // find the characters ei that follow a character other than c
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*"; // we want the whole word in which our pattern appears
	regex r(pattern); // construct a regex to find pattern
	smatch results; // define an object to hold the results of a search
	string test_str = "receipt freind theif receive"; // define a string that has text that does and doesn’t match pattern
	if (regex_search(test_str, results, r)) // if there is a match // use r to find a match to pattern in test_str
		cout << results.str() << endl; // print the matching word
}

void Specifying_Options_for_a_regex_Object() {
	regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase); // one or more alphanumeric characters followed by a ’.’ followed by "cpp" or "cxx" or "cc"
	smatch results;
	string filename;
	while (cin >> filename)
		if (regex_search(filename, results, r))
			cout << results.str() << endl; // print the current match
}

void Errors_in_Specifying_or_Using_a_Regular_Expression() {
	try {
		regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase); // error: missing close bracket after alnum; the constructor will throw
	}
	catch (regex_error e) {
		cout << e.what() << "\ncode: " << e.code() << endl;
	}
}

#ifdef OFF
void Regular_Expression_Classes_and_the_Input_Sequence_Type() {
	cmatch results; // will match character array input sequences
	if (regex_search("myfile.cc", results, r))
		cout << results.str() << endl; // print the current match
}
#endif

int main() {
	print_file_line();

	Using_the_Regular_Expression_Library();
	//Specifying_Options_for_a_regex_Object();
	//Errors_in_Specifying_or_Using_a_Regular_Expression();
}
#endif
