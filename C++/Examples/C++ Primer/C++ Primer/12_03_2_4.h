#pragma once

#include <iostream>
#include <set>
#include <vector>
using std::ifstream;
using std::istringstream;
using std::ostream;
using std::set;
using std::shared_ptr;
using std::string;
using std::vector;

#ifndef EX_12_33
using line_no = vector<string>::size_type;
#endif

#ifndef The_QueryResult_Class
class QueryResult { //VER2
	friend ostream &print(ostream &, const QueryResult &);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f1) : sought(s), lines(p), file(f1) {}
#ifndef EX_12_33
	using line_it = set<line_no>::iterator;
	line_it begin() const;
	line_it end() const;
	shared_ptr<vector<string>> get_file() const;
#endif
private:
	string sought; // word this query represents
	shared_ptr<set<line_no>> lines; //TEST! //																																					lines it’s on
	shared_ptr<vector<string>> file; //TEST! //																																					input file
};
#endif

shared_ptr<vector<string>> QueryResult::get_file() const {
	return file;
}

#include "12_03_2_5.h" //MINE This header must be here.