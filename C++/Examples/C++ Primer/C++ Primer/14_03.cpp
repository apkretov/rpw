#include "14_01.h"
using namespace std;

#ifndef Arithmetic_and_Relational_Operators
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) { // assumes that both objects refer to the same book
	Sales_data sum = lhs; // copy data members from lhs into sum
	sum += rhs; // add rhs into sum
	return sum;
}
#endif

#ifdef ON

#include "../../stdafx.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
	print_file_line();
	
	ifstream in(argv[1]);
	Sales_data s1(in);
	Sales_data s2(in);
	cout << s1 << '\n' << s2 << '\n';
	auto s3 = s1 + s2;
	cout << s3 << '\n';

	return 0;
}
#endif