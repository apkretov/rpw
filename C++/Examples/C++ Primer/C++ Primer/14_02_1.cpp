#include "14_01.h"
using namespace std;

#ifndef The_Sales_data_Output_Operator
ostream &operator<<(ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}
#endif

#ifdef ON

#include "../../stdafx.h"

int main(int argc, char *argv[]) {
	print_file_line();

	Sales_data s{"aaa", 111, 222};
	cout << s << '\n';

	return 0;
}
#endif