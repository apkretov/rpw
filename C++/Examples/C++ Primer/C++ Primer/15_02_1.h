#pragma once

#include <string>
using std::string;

#ifndef Defining_a_Base_Class
class Quote { //VER2
public:
	Quote() = default; // = default see § 7.1.4 (p. 264)
	Quote(const string &book, double sales_price) : bookNo(book), price(sales_price) {}
	
	string isbn() const { 
		return bookNo; 
	}
	
	virtual double net_price(size_t n) const { // returns the total sales price for the specified number of items // derived classes will override and apply different discount algorithms
		return n * price;
	}

	virtual ~Quote() = default; //TEST!! //																																						dynamic binding for the destructor
private:
	string bookNo; // ISBN number of this item
protected:
	double price = 0.0; // normal, undiscounted price
};
#endif