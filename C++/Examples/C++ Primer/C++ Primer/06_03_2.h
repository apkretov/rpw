#pragma once

#include <string>
using std::string;

namespace How_Values_Are_Returned {
	const string &shorterString(const string &s1, const string &s2);
	string make_plural(size_t ctr, const string &word, const string &ending);
}
