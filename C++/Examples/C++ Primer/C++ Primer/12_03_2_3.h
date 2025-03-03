#pragma once

#include <algorithm> 
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;

#ifndef The_query_Function
QueryResult TextQuery::query(const string &sought) const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>); //TEST! //																														we’ll return a pointer to this set if we don’t find sought

	auto loc = wm.find(sought); // use find and not a subscript to avoid adding words to wm!
	if (loc == wm.end())
		return QueryResult(sought, nodata, file); // not found
	else
		return QueryResult(sought, loc->second, file);
}
#endif

#ifndef Printing_the_Results
ostream &print(ostream &os, const QueryResult &qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl; // if the word was found, print the count and all occurrences
	for (auto num : *qr.lines) // print each line in which the word appeared // for every element in the std::set
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl; // don’t confound the user with text lines starting at 0
	return os;
}
#endif

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