#pragma once

#include "12_03_2_1.h" // Keep the headers sequence.
#include "12_03_2_4.h"
#include "12_03_2_3.h"
using namespace std;

#ifndef The_Query_base_and_Query_Classes
class Query_base { // abstract class acts as a base class for concrete query types; all members are private
	friend class Query;
protected:
	using line_no = TextQuery::line_no; //TEST //																																					used in the eval functions
	virtual ~Query_base() = default; //TEST!
private:
	virtual QueryResult eval(const TextQuery &) const = 0; // eval returns the QueryResult that matches this Query
	virtual string rep() const = 0; // rep is a string representation of the query
};
#endif

#ifndef The_Query_Class // interface class to manage the Query_base inheritance hierarchy
class Query { //VER1
	friend Query operator~(const Query &); // these operators need access to the shared_ptr constructor
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);
public:
	Query(const string &); // builds a new WordQuery
	
	QueryResult eval(const TextQuery &t) const { // interface functions: call the corresponding Query_base operations
		return q->eval(t);
	}

	string rep() const {
		return q->rep(); 
	}
private:
	Query(shared_ptr<Query_base> query) : q(query) {} //TEST!
	shared_ptr<Query_base> q;
};
#endif

#ifndef The_Query_Output_Operator
static ostream &operator<<(ostream &os, const Query &query) {
	return os << query.rep(); //Query::rep makes a virtual call through its Query_base pointer to rep()
}
#endif