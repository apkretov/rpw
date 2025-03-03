#pragma once

#ifndef ON

#include <string>
#include <vector>

struct PersonInfo { // members are public by default; see § 7.2 (p. 268)
	std::string name;
	std::vector<std::string> phones;
};

//MINE
using vpi = std::vector<PersonInfo>; 
void Using_an_istringstream(vpi &people);
#endif