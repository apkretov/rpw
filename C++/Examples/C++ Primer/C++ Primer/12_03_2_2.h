#pragma once

using namespace std;

#ifndef The_QueryResult_Class
class QueryResult { //VER1
	friend ostream &print(ostream &, const QueryResult &);
public:
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f1) : sought(s), lines(p), file(f1) {}
private:
	string sought; // word this query represents
	shared_ptr<set<line_no>> lines; //TEST! //																																					lines it’s on
	shared_ptr<vector<string>> file; //TEST! //																																					input file
};
#endif
