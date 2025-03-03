#ifdef ON

#include <iostream>
#include <fstream>
#include "../../stdafx.h"
#include "12_03_2_1.h" // Keep the headers sequence.
#include "12_03_2_2.h"
#include "12_03_2_3.h"
using namespace std;

int main(int argc, char *argv[]) {
	using namespace std;
	print_file_line();

	//MINE
	ifstream in(argv[1]);
	runQueries(in);
	
	return 0;
}
#endif