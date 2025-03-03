#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "15_07_2.h"
#include "15_06.h"
#include "15_07_4.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();
	
	Bulk_quote b("aaa", 100, 10, 1);
	cout << "b.isbn() = " << b.isbn() << '\n';

	return 0;
}
#endif

#ifdef EX_15_27

#include <iostream>
#include "../../stdafx.h"
#include "15_07_3_1.h"
#include "15_07_3_2.h"
#include "15_07_4.h"
#include "15_07_3_4.h" // The above header must be included prior to this one.

using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();
	
	objects();
	//pointers_object();
	//pointers_new();
	
	return 0;
}
#endif