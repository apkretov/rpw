#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "15_09_2.h"
#include "15_09_3_2.h"
#include "15_09_4_1.h"
using namespace std;

void The_Query_Output_Operator(const string &file) {
	//MINE
	ifstream in(file);
	string sought1;
	string sought2;
	in >> sought1 >> sought2;
	cout << "sought1 = " << sought1 << '\n';
	cout << "sought2 = " << sought2 << '\n';
	cout << "Query(" << sought1 << ") & Query(" << sought2 << ") = ";

	Query andq = Query(sought1) & Query(sought2);
	cout << andq << endl;
}

int main(int argc, char *argv[]) {
	print_file_line();

	The_Query_Output_Operator(argv[1]);

	return 0;
}
#endif
