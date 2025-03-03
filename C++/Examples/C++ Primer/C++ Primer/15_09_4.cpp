#ifdef EX_15_39

#include <iostream>
#include "../../stdafx.h"
#include "15_09_2.h"
#include "15_09_3_2.h"
#include "15_09_4_1.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	ifstream infile(argv[1]);
	TextQuery tq(infile);

	Query q = Query("fiery") & Query("bird") | Query("wind");
	print(cout, q.eval(tq));
	
	cout << q << endl;
	
	return 0;
}
#endif