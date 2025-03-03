#ifdef ON

#include <fstream>
#include <iostream>
#include <regex>
#include "../../stdafx.h"
using namespace std;

void Using_an_sregex_iterator(const string & file) {
#ifdef ORIG
	string pattern("[^c]ei"); // find the characters ei that follow a character other than c
#else //MINE
		cout << "The matches found:\n";
	#ifdef ALICE
		string pattern("[^c]lice");
	#else //NUMBERS
		string pattern("[^c]00");
	#endif
#endif
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*"; // we want the whole word in which our pattern appears
	regex r(pattern, regex::icase); // we’ll ignore case in doing the match
	for (sregex_iterator it(file.begin(), file.end(), r), end_it; // it will repeatedly call regex_search to find all matches in file
		it != end_it; ++it)
		cout << it->str() << endl; // matched word
}

void Using_the_Match_Data(const string &file) {
#ifdef ORIG
	string pattern("[^c]ei"); // find the characters ei that follow a character other than c
#else //MINE
		cout << "The matches found:\n";
	#ifndef ALICE
		string pattern("[^c]lice");
	#else //NUMBERS
		string pattern("[^c]00");
	#endif
#endif
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*"; // we want the whole word in which our pattern appears
	regex r(pattern, regex::icase); // we’ll ignore case in doing the match
	
	for (sregex_iterator it(file.begin(), file.end(), r), end_it; // same for loop header as before
		it != end_it; ++it) {
		auto pos = it->prefix().length(); // size of the prefix
		pos = pos > 40 ? pos - 40 : 0; // we want up to 40 characters
		cout << it->prefix().str().substr(pos) // last part of the prefix
			<< "\n\t\t>>> " << it->str() << " <<<\n" // matched word
			<< it->suffix().str().substr(0, 40) // first part of the suffix
			<< endl;
	}
}

int main(int, char *argv[]) {
	print_file_line();

	//MINE
	fstream in(argv[1]);
	string file((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	cout << file << '\n';

	Using_an_sregex_iterator(file);
	//Using_the_Match_Data(file);
}
#endif
