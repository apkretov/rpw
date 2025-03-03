#include <iostream> // ch15/ex15.42_b @ https://github.com/Mooophy/Cpp-Primer/tree/master/ch15/ex15.42_b
using std::cout; using std::cin; using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "queryhistory.h"
#include "queryresult.h"
#include "textquery.h"
#include "query.h"
#include "andquery.h"
#include "orquery.h"
#include "notquery.h"
#include "../../stdafx.h" //MINE

int main() {
	print_file_line();

	ifstream fin("test.txt");
	TextQuery text(fin);
	QueryHistory history;
	Query q0("Alice");
	Query q1("hair");
	Query q2("Daddy");

	history.add_query(q0);
	history.add_query(q1);
	history[0] = history[0] | q2;

	auto result = history[0].eval(text);
	print(cout, result);
	
    return 0;
}
