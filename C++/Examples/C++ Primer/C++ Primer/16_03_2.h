#pragma once

#include "16_03_1.h"

#pragma region Nontemplate and Template Overloads
string debug_rep(const string &s) { // print strings inside double quotes
	return '"' + s + '"';
}
#pragma endregion

#pragma region Overloaded Templates and Conversions
string debug_rep(char *p) { // convert the character pointers to string and call the string version of debug_rep
	return debug_rep(string(p));
}

string debug_rep(const char *p) {
	return debug_rep(string(p));
}
#pragma endregion
