#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "06_03_2.h"
#include "16_01_4_2.h"
using std::set;
using std::map;
using std::make_tuple;
using std::shared_ptr;
using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;
using std::tuple;

#ifndef Defining_the_Query_Program_Classes
class TextQuery { //VER4 (DO NOT USE IT EXCEPT FOR EX_17_03!) With tuple instead of QueryResult.
public:
	using line_no = vector<string>::size_type;
#pragma region EX_17_03
	using QueryResult = tuple<string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>>;
	explicit TextQuery(ifstream &);
#pragma endregion
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

#ifndef The_query_Function
#pragma region EX_17_03
TextQuery::QueryResult TextQuery::query(const string &sought) const {
#pragma endregion
	static shared_ptr<set<line_no>> nodata(new set<line_no>); //TEST! //																														we’ll return a pointer to this set if we don’t find sought
	auto loc = wm.find(sought); // use find and not a subscript to avoid adding words to wm!
	if (loc == wm.end())
#pragma region EX_17_03
		return make_tuple(sought, nodata, file); // not found
	else
		return make_tuple(sought, loc->second, file);
#pragma endregion
}
#endif