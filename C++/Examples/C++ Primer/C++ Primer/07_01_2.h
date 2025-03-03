#ifdef Defining_the_Revised_Sales_data_Class
 
#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

struct Sales_data { //VER02
	std::string isbn() const { return bookNo; } // new members: operations on Sales_data objects
	Sales_data &combine(const Sales_data &);
	double avg_price() const;

	std::string bookNo; // data members are unchanged from § 2.6.1 (p. 72)
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data &, const Sales_data &); // nonmember Sales_data interface functions
ostream &print(ostream &, const Sales_data &);
istream &read(istream &, Sales_data &);

#endif
#endif
