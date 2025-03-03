#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "15_02_2_2.h"
#include "15_04_1.h"
using namespace std;

void Classes_with_Pure_Virtuals_Are_Abstract_Base_Classes() {
	// Disc_quote declares pure virtual functions, which Bulk_quote will override
	//TEST Disc_quote discounted; // error: can’t define a Disc_quote object
	Bulk_quote bulk; // ok: Bulk_quote has no pure virtual functions
}

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_15_17

#include <iostream>
#include "../../stdafx.h"
#include "15_04_1.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();
	
	//ERR Disc_quote d;
	
	return 0;
}
#endif