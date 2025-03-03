#ifdef ON

#include <iostream>
#include <string>
#include "../../stdafx.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

#ifndef Aggregate_Classes
	struct Data {
		int ival;
		string s;
	};

	//TEST! Data val1 = {0, "Anna"}; //																																					val1.ival = 0; val1.s = string("Anna")
	//TEST! Data val2 = {"Anna" , 1024}; //																																				error: can’t use "Anna" to initialize ival, or 1024 to initialize s
	Data val3 = {10}; //TEST! //MINE
#endif
	
	//MINE
	cout << "val3.ival = " << val3.ival << '\n';
	cout << "val3.s = " << val3.s << '\n';

	return 0;
}
#endif