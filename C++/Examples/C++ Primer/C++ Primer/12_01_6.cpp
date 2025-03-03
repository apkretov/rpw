#ifdef ON
#include <iostream>
#include "../../stdafx.h"
#include "12_01_6_3.h"
#include "12_01_6_1.h"
#include "12_01_6_util.h"
using namespace std;

#ifndef Checked_Pointer_Class
void weak_ptr_() {
	auto p = make_shared<int>(42);
	weak_ptr<int> wp(p); //TEST!! //																																									wp weakly shares with p; use count in p is unchanged

	//TEST!!! cout << *wp << '\n'; //MINE

	if (shared_ptr<int> np = wp.lock()) { //TEST!!! //																																					true if np is not null
		// inside the if, np shares its object with p
		cout << "*np = " << *np << '\n'; //MINE
	}
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();

	weak_ptr_();
	//test_StrBlob();

	return 0;
}
#endif