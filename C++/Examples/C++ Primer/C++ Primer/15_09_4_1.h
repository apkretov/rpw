#pragma once

#include <algorithm>
#include "15_09_3_1.h"

#ifndef OrQuery_eval // OrQuery::eval
QueryResult OrQuery::eval(const TextQuery &text) const { // returns the union of its operands’ result sets
	auto right = rhs.eval(text), left = lhs.eval(text); // virtual calls through the Query members, lhs and rhs // the calls to eval return the QueryResult for each operand
	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end()); // copy the line numbers from the left-hand operand into the result set
	ret_lines->insert(right.begin(), right.end()); // insert lines from the right-hand operand
	return QueryResult(rep(), ret_lines, left.get_file()); // return the new QueryResult representing the union of lhs and rhs
}
#endif

#ifndef AndQuery_eval // AndQuery::eval
QueryResult AndQuery::eval(const TextQuery &text) const { // returns the intersection of its operands’ result sets
	auto left = lhs.eval(text), right = rhs.eval(text); // virtual calls through the Query operands to get result sets for the operands
	auto ret_lines = make_shared<set<line_no>>(); // set to hold the intersection of left and right
	set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin())); // writes the intersection of two ranges to a destination iterator // destination iterator in this call adds elements to ret
	return QueryResult(rep(), ret_lines, left.get_file());
}
#endif

#ifndef NotQuery_eval // NotQuery::eval
QueryResult NotQuery::eval(const TextQuery &text) const { // returns the lines not in its operand’s result set
	auto result = query.eval(text); // virtual call to eval through the Query operand
	auto ret_lines = make_shared<set<line_no>>(); // start out with an empty result set
	auto beg = result.begin(), end = result.end(); // we have to iterate through the lines on which our operand appears
	auto sz = result.get_file()->size(); // for each line in the input file, if that line is not in result, // add that line number to ret_lines
	
	for (size_t n = 0; n != sz; ++n) {
		if (beg == end || *beg != n) // if we haven’t processed all the lines in result // check whether this line is present
			ret_lines->insert(n); // if not in result, add this line
		else if (beg != end)
			++beg; // otherwise get the next line number in result if there is one
	}
	
	return QueryResult(rep(), ret_lines, result.get_file());
}
#endif