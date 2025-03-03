#pragma once

#include <string>

#ifndef inline_Functions_Avoid_Function_Call_Overhead
inline const std::string &shorterString(const std::string &s1, const std::string &s2) { // inline version: find the shorter of two strings
	return s1.size() <= s2.size() ? s1 : s2;
}
#endif

constexpr int mine1() {
	return 111;
}