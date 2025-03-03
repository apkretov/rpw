#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "15_08_1_1.h"
#include "15_08_1_2.h"
using namespace std;

#ifndef Hiding_the_Pointers
void Hiding_the_Pointers_() {
	Basket bsk;
	bsk.add_item(make_shared<Quote>("123", 45));
	bsk.add_item(make_shared<Bulk_quote>("345", 45, 3, .15));
	bsk.total_receipt(cout); //MINE
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	
	Hiding_the_Pointers_();

	return 0;
}
#endif

#ifdef EX_15_30

#include <iostream>
#include "../../stdafx.h"
#include "15_08_1_5.h"
#include "15_08_1_2.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	Basket bsk;
	
	bsk.add_item(Quote("aaa", 100));
	bsk.add_item(Bulk_quote("bbb", 200, 20, 2));
	bsk.total_receipt(cout);
	cout << '\n';

	Quote q("aaa", 300);
	Bulk_quote b("bbb", 400, 40, 4);
	bsk.add_item(q);
	bsk.add_item(b);
	bsk.total_receipt(cout);

	return 0;
}
#endif
