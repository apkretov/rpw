#pragma once

#ifdef EX_12_32

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "06_03_2.h"
#include "13_06_3.h"
#include "14_07.h"
using namespace std;
using namespace How_Values_Are_Returned;

#ifndef Defining_the_Query_Program_Classes
class QueryResult; // declaration needed for return type in the query function

class TextQuery { //VER2 (DO NOT USE IT EXCEPT FOR EX_12_32!) With StrBlob instead of shared_ptr<vector<string>>.
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream &);
	QueryResult query(const string &) const;
private:
#ifdef EX_12_32
	StrBlob file; // input file
#endif
	map<string, shared_ptr<set<line_no>>> wm; // map of each word to the set of the lines in which that word appears
};

using line_no = TextQuery::line_no; //MINE
#endif

#ifndef The_TextQuery_Constructor
#ifdef EX_12_32
TextQuery::TextQuery(ifstream &is) { // read the input file and build the map of lines to line numbers
#endif
	string text;

	while (getline(is, text)) { // for each line in the file
#ifdef EX_12_32 
		file.push_back(text); // remember this line of text
		int n = file.size() - 1; // the current line number
#endif
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
#endif