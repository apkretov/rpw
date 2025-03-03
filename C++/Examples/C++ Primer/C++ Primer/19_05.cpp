#ifdef ON

#include <fstream>
#include <iostream>
#include "../../stdafx.h"
//#include "19_05.h"
#include "19_05_2.h"
using namespace std;

#ifndef Using_the_TextQuery_Class
void runQueries(ifstream &infile) { // infile is an ifstream that is the file we want to query
	TextQuery tq(infile); // store the file and build the query map

	while (true) { 	// iterate with the user: prompt for a word to find and print results
		cout << "enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q") // stop if we hit end-of-file on the input or if a ’q’ is entered
			break;
		print(cout, tq.query(s)) << endl; // run the query and print the results
	}
}
#endif

int main(int, char *argv[]) {
	print_file_line();

	ifstream in(argv[1]);
	runQueries(in);

	return 0;
}
#endif
