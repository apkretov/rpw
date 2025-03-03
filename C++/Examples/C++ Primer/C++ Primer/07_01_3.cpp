#include <iostream>
using namespace std;
#ifdef Defining_the_Revised_Sales_data_Class
#include "07_01_2.h"
#elif Defining_the_Sales_data_Constructors
#include "07_01_4.h"
#elif Access_Control_and_Encapsulation
#include "07_02.h"
#elif Friends
#include "07_02_1.h"
#elif Default_Arguments_and_Constructors
#include "07_05_1.h"
#elif Delegating_Constructors
#include "07_05_2.h"
#elif !Suppressing_Implicit_Conversions_Defined_by_Constructors
#include "07_05_4.h"
#endif

#ifndef Access_Control_and_Encapsulation
#ifndef Defining_the_read_and_print_Functions
istream &read(istream &is, Sales_data &item) { // input transactions contain ISBN, number of copies sold, and sales price
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

ostream &print(ostream &os, const Sales_data &item) {
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}
#endif
#endif

#ifndef Defining_the_add_Function
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs; // copy data members from lhs into sum
	sum.combine(rhs); // add data members from rhs into sum
	return sum;
}
#endif

#ifdef ON
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE
	
	Sales_data sd1;
	Sales_data sd2;
	
	read(cin, sd1);
	print(cout, sd1);
	cout << '\n';
	
	read(cin, sd2);
	print(cout, sd2);
	cout << '\n';
	
	Sales_data sum{add(sd1, sd2)};
	print(cout, sum);
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_07_10
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Sales_data sd1, sd2;

	if (read(read(cin, sd1), sd2))
		print(print(cout, sd1), sd2);
	else
		cout << "Entering sd1 & sd2 failed.";
	cout << '\n';

	return 0;
}
#endif