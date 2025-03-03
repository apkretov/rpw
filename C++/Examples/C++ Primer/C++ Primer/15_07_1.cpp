#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "15_02_1.h"
#include "15_06.h"
#include "15_04_2.h"
using namespace std;

void Virtual_Destructors() {
	Quote *itemP = new Quote; // same static and dynamic type
	delete itemP; // destructor for Quote called
	itemP = new Bulk_quote; // static and dynamic types differ
	delete itemP; //TEST! //																																										destructor for Bulk_quote called
}

int main(int agrc, char *agrv[]) {
	print_file_line();

	Virtual_Destructors();

	return 0;
}
#endif