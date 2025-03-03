#ifdef EX_12_32
#define EX_12_32

#include <iostream>
#include <fstream>
#include "../../stdafx.h"
#include "12_03_2_6.h" // Keep the headers sequence.
#include "12_03_2_7.h"
#include "12_03_2_8.h"
using namespace std;

int main(int argc, char *argv[]) {
	using namespace std;
	print_file_line();

	ifstream in(argv[1]);
	runQueries(in);

	return 0;
}
#endif

#ifdef EX_12_33

#include <iostream>
#include "../../stdafx.h"
#include "12_03_2_1.h" // Keep the headers sequence.
#include "12_03_2_4.h"
#include "12_03_2_3.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	//MINE
	ifstream in(argv[1]);
	runQueries(in);

	return 0;
}
#endif
