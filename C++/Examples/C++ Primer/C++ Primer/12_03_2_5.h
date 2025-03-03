#pragma once

#ifndef EX_12_33
using line_it = QueryResult::line_it;

line_it QueryResult::begin() const {
	return lines->begin();
}

line_it QueryResult::end() const {
	return lines->end();
}
#endif