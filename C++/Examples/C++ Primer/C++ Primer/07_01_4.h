#ifndef Defining_the_Sales_data_Constructors

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

struct Sales_data { //VER03
	Sales_data() = default; //TEST // constructors added
	Sales_data(const std::string &s) : bookNo(s) {}
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p *n) {}
	Sales_data(std::istream &);
	
	std::string isbn() const { return bookNo; } // other members as before
	Sales_data &combine(const Sales_data &);
	double avg_price() const;
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data &, const Sales_data &); // nonmember Sales_data interface functions
ostream &print(ostream &, const Sales_data &);
istream &read(istream &, Sales_data &);

#endif
#endif
