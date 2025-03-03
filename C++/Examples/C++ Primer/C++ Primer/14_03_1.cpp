#include "14_03_1_1.h"
using namespace std;

#ifndef Equality_Operators
bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() == rhs.isbn() &&
		lhs.units_sold == rhs.units_sold &&
		lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs) {
	return !(lhs == rhs);
}
#endif

#ifdef ON

#include <iostream>
#include <fstream>
#include "../../stdafx.h"

int main(int argc, char *argv[]) {
	print_file_line();

	fstream in(argv[1]);
	Sales_data s1(in), s2(in), s3(s1);
	cout << "s1 = " << s1 << '\n';
	cout << "s2 = " << s2 << '\n';
	cout << "s3 = " << s3 << "\n\n";
	cout << "s1 == s2 = " << boolalpha << (s1 == s2) << '\n';
	cout << "s3 == s1 = " << boolalpha << (s3 == s1) << '\n';

	return 0;
}
#endif