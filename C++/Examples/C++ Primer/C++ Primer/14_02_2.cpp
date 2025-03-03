#include "14_01.h"
using namespace std;

#ifndef The_Sales_data_Input_Operator
istream &operator>>(istream &is, Sales_data &item) {
	double price; // no need to initialize; we’ll read into price before we use it
	is >> item.bookNo >> item.units_sold >> price;
	if (is) // check that the inputs succeeded
		item.revenue = item.units_sold * price;
	else
		item = Sales_data(); //TEST! //																																									input failed: give the object the default state
	return is;
}
#endif

#ifdef ON

#include "../../stdafx.h"

void mine1() {
	Sales_data s(cin);
	cout << s << '\n';
}

void mine2() {
	Sales_data s;
	cin >> s;
	cout << s << '\n';
}

int main(int argc, char *argv[]) {
	print_file_line();
	
	//mine1();
	mine2();

	return 0;
}
#endif