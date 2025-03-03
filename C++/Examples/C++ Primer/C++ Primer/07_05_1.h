#pragma once

#ifdef Default_Arguments_and_Constructors

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

class Sales_data { //VER06
	friend Sales_data add(const Sales_data &, const Sales_data &); // friend declarations for nonmember Sales_data operations added
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);
public: // other members and access specifiers as before
	//ERR Sales_data() = default;

	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p *n) {
	}

	Sales_data(const std::string &s = "") : bookNo(s) {} // defines the default constructor as well as one that takes a	string argument
	Sales_data(std::istream &);
	std::string isbn() const { return bookNo; }
	Sales_data &combine(const Sales_data &);

	double avg_price() const { //MINE
		return units_sold ? revenue / units_sold : 0;
	}
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

#endif
#endif

