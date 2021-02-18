#pragma once
#include <fstream>
using std::ifstream;
#include <string>
using std::string;

class symbol {
public:
	symbol(string, string);
	string name; // symbol name.
	string file; // File name with the symbol history.
};

