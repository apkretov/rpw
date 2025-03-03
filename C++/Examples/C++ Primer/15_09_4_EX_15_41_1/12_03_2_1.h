#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "06_03_2.h"
using namespace std;
using namespace How_Values_Are_Returned;

#ifndef Defining_the_Query_Program_Classes
class QueryResult; // declaration needed for return type in the query function

class TextQuery { //VER1
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream &);
	QueryResult query(const string &) const;
private:
	shared_ptr<vector<string>> file; // input file
	map<string, shared_ptr<set<line_no>>> wm; // map of each word to the set of the lines in which that word appears
};

using line_no = TextQuery::line_no; //MINE
#endif

#ifndef The_TextQuery_Constructor
TextQuery::TextQuery(ifstream &is) : file(new vector<string>) { // read the input file and build the map of lines to line numbers
	string text;

	while (getline(is, text)) { // for each line in the file
		file->push_back(text); // remember this line of text
		int n = file->size() - 1; // the current line number

		istringstream line(text); // separate the line into words
		string word;
		while (line >> word) { // for each word in that line
			auto &lines = wm[word]; // if word isn’t already in wm, subscripting adds a new entry // lines is a shared_ptr
			if (!lines) // that pointer is null the first time we see word
				lines.reset(new set<line_no>); // allocate a new set
			lines->insert(n); // insert this line number
		}
	}
}
#endif
