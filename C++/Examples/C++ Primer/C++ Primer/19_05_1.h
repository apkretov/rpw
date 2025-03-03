#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "06_03_2.h"
#include "16_01_4_2.h"
using std::cin;
using std::ifstream;
using std::istringstream;
using std::map;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;
using namespace How_Values_Are_Returned;

#ifndef Defining_the_Query_Program_Classes
class TextQuery { //VER4 With a QueryResult nested class.
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream &);
#pragma region Declaring a Nested Class
	class QueryResult; //TEST! //																															nested class to be defined later
#pragma endregion // other members as in § 12.3.2 (p. 487)
	QueryResult query(const string &) const;
private:
	shared_ptr<vector<string>> file; // input file
	map<string, shared_ptr<set<line_no>>> wm; // map of each word to the set of the lines in which that word appears
};

using line_no = TextQuery::line_no; //MINE
#endif

#ifndef The_TextQuery_Constructor
#pragma region EX_16_22
TextQuery::TextQuery(ifstream &is) : file(new vector<string>, DebugDelete()) { // read the input file and build the map of lines to line numbers  
#pragma endregion
	string text;

	while (getline(is, text)) { // for each line in the file
		file->push_back(text); // remember this line of text
		int n = file->size() - 1; // the current line number

		istringstream line(text); // separate the line into words
		string word;
		while (line >> word) { // for each word in that line
			auto &lines = wm[word]; // if word isn’t already in wm, subscripting adds a new entry // lines is a shared_ptr
			if (!lines) // that pointer is null the first time we see word
#pragma region EX_16_22
				lines.reset(new set<line_no>, DebugDelete()); // allocate a new set
#pragma endregion
			lines->insert(n); // insert this line number
		}
	}
}
#endif
