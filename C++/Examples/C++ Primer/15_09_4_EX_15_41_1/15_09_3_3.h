#pragma once

#include "15_09_4_2.h"

#ifndef The_WordQuery_Class
class WordQuery : public Query_base {
	friend class Query; // Query uses the WordQuery constructor

	WordQuery(const string &s) : query_word(s) {}

	QueryResult eval(const TextQuery &t) const { // concrete class: WordQuery defines all inherited pure virtual functions
		return t.query(query_word);
	}

	string rep() const {
		return query_word;
	}

	string query_word; // word for which to search
};
#endif

#ifndef The_NotQuery_Class_and_the_Operator_ // The NotQuery Class and the ~ Operator
class NotQuery : public Query_base { //VER2 With built-in pointers vs. shared_ptrs
	friend Query operator~(const Query &);
	NotQuery(const Query &q) : query(q) {}

	string rep() const { // concrete class: NotQuery defines all inherited pure virtual functions
		return "~(" + query.rep() + ")";
	}

	QueryResult eval(const TextQuery &) const;
	Query query;
};

inline Query operator~(const Query &operand) {
#ifndef EX_15_41
	return new NotQuery(operand);
#endif
}
#endif

#ifndef The_BinaryQuery_Class
class BinaryQuery : public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, string s) : lhs(l), rhs(r), opSym(s) {}

	string rep() const { // abstract class: BinaryQuery doesn’t define eval
		return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
	}

	Query lhs, rhs; // right- and left-hand operands
	string opSym; // name of the operator
};
#endif

#ifndef The_AndQuery_and_OrQuery_Classes_and_Associated_Operators
class AndQuery : public BinaryQuery { //VER2 With built-in pointers vs. shared_ptrs 
	friend Query operator&(const Query &, const Query &);
	AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") {}
	QueryResult eval(const TextQuery &) const; // concrete class: AndQuery inherits rep and defines the remaining pure virtual
};

inline Query operator&(const Query &lhs, const Query &rhs) {
#ifndef EX_15_41
	return new AndQuery(lhs, rhs);
#endif
}

class OrQuery : public BinaryQuery { //VER2 With built-in pointers vs. shared_ptrs 
	friend Query operator|(const Query &, const Query &);
	OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") {}
	QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs) {
#ifndef EX_15_41
	return new OrQuery(lhs, rhs);
#endif
}
#endif
