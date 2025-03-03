#pragma once // This separate header is needed because the definition of the Query constructor cannot be placed in 15_09_3.cpp, which in turn does not let 12_03_1.cpp compile.

#ifndef The_WordQuery_Class

#include "15_09_3_1.h"

inline Query::Query(const string &s) : q(new WordQuery(s)) {}
#endif