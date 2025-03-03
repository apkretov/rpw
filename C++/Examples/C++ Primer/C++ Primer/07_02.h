#ifdef Access_Control_and_Encapsulation

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

class Sales_data { //VER04
public: // access specifier added
	Sales_data() = default;
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p * n) {
	}
	Sales_data(const std::string &s) : bookNo(s) {}
	Sales_data(std::istream &);
	std::string isbn() const { return bookNo; }
	Sales_data &combine(const Sales_data &);
private: // access specifier added
	double avg_price() const {
		return units_sold ? revenue / units_sold : 0;
	}
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data &, const Sales_data &); // nonmember Sales_data interface functions
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);

#endif
#endif
