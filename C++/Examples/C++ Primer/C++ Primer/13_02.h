#pragma once

#include <string>

#ifdef EX_13_02
class HasPtr {
	std::string *ptr;
public:
	HasPtr(std::string *p = new std::string);
};
#endif