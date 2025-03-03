#ifdef ON

#include "../../stdafx.h"
#include "15_01_1.h"
#include "15_01_2.h"
using namespace std;

void Dynamic_Binding_() {
	// basic has type Quote; bulk has type Bulk_quote
	Quote basic; //MINE
	Bulk_quote bulk; //MINE
	
	print_total(cout, basic, 20); // calls Quote version of net_price
	cout << '\n'; //MINE
	print_total(cout, bulk, 20); // calls Bulk_quote version of net_price
}

int main(int argc, char *argv[]) {
	print_file_line();

	Dynamic_Binding_();

	return 0;
}
#endif