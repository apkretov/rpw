#pragma once

#ifdef EX_12_32

#include <iostream>
#include <set>
#include <vector>
#include "13_06_3.h"
using namespace std;

#ifndef The_QueryResult_Class
class QueryResult { //VER3 (DO NOT USE IT EXCEPT FOR EX_12_32!) With StrBlob instead of shared_ptr<vector<string>>.
	friend ostream &print(ostream &, const QueryResult &);
public:
#ifdef EX_12_32
	QueryResult(string s, shared_ptr<set<line_no>> p, StrBlob f) : sought(s), lines(p), file(f) {}
#endif
#ifndef EX_12_33
	using line_it = set<line_no>::iterator;
	line_it begin() const;
	line_it end() const;
#ifdef EX_12_32
	StrBlob get_file() const;
#endif
#endif
private:
	string sought; // word this query represents
	shared_ptr<set<line_no>> lines; // lines it’s on
#ifdef EX_12_32
	StrBlob file; // input file
#endif
};
#endif

StrBlob QueryResult::get_file() const {
	return file;
}

#include "12_03_2_5.h" //MINE This header must be here.
#endif