#pragma once

#include "19_05_1.h"

#pragma region Defining a Nested Class outside of the Enclosing Class
class TextQuery::QueryResult { //TEST!! //																												we’re defining the QueryResult class that is a member of class TextQuery
	friend ostream &print(ostream &, const QueryResult &); // in class scope, we don’t have to qualify the name of the QueryResult parameters
public:
	QueryResult(string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>); // no need to define QueryResult::line_no; a nested class can use a member // of its enclosing class without needing to qualify the member’s name
	// other members as in § 12.3.2 (p. 487)
#ifndef The_QueryResult_Class
#ifndef EX_12_33
	using line_it = set<line_no>::iterator;
	line_it begin() const;
	line_it end() const;
	shared_ptr<vector<string>> get_file() const;
#endif
	static int static_mem; //MINE
private:
	string sought; // word this query represents
	shared_ptr<set<line_no>> lines; // lines it’s on
	shared_ptr<vector<string>> file; // input file
#endif
};
#pragma endregion

#pragma region Defining the Members of a Nested Class
TextQuery::QueryResult::QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) : sought(s), lines(p), file(f) {} //TEST! //	defining the member named QueryResult for the class named QueryResult // that is nested inside the class TextQuery
#pragma endregion

#pragma region Nested-Class static Member Definitions
int TextQuery::QueryResult::static_mem = 1024; // defines an int static member of QueryResult // which is a class nested inside TextQuery
#pragma endregion

#pragma region Name Lookup in Nested Class Scope
TextQuery::QueryResult TextQuery::query(const string &sought) const { // return type must indicate that QueryResult is now a nested class
	static shared_ptr<set<line_no>> nodata(new set<line_no>); // we’ll return a pointer to this set if we don’t find sought
	auto loc = wm.find(sought); // use find and not a subscript to avoid adding words to wm!
	if (loc == wm.end())
		return QueryResult(sought, nodata, file); // not found
	else
		return QueryResult(sought, loc->second, file);
}
#pragma endregion

#pragma region MINE
shared_ptr<vector<string>> TextQuery::QueryResult::get_file() const {
	return file;
}
#pragma endregion

#ifndef EX_12_33
using line_it = TextQuery::QueryResult::line_it; //MINE

line_it TextQuery::QueryResult::begin() const { //MINE
	return lines->begin();
}

line_it TextQuery::QueryResult::end() const { //MINE
	return lines->end();
}
#endif

#ifndef Printing_the_Results
ostream &print(ostream &os, const TextQuery::QueryResult &qr) { //MINE
	os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl; // if the word was found, print the count and all occurrences
	for (auto num : *qr.lines) // print each line in which the word appeared // for every element in the std::set
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl; // don’t confound the user with text lines starting at 0
	return os;
}
#endif
