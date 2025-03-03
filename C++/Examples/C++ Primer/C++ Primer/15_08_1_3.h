#pragma once

#include <string>

#ifndef Defining_a_Base_Class
class Quote { //VER4
public:
	Quote() = default; // = default see § 7.1.4 (p. 264)
	Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
#ifndef Move_Operations_and_Inheritance
	Quote(const Quote &) = default; // memberwise copy
	Quote(Quote &&) = default; // memberwise copy
	Quote &operator=(const Quote &) = default; // copy assign
	Quote &operator=(Quote &&) = default; // move assign
#endif // other members as before

	std::string isbn() const {
		return bookNo;
	}

	virtual double net_price(std::size_t n) const { // returns the total sales price for the specified number of items // derived classes will override and apply different discount algorithms
		return n * price;
	}

	virtual ~Quote() = default; // dynamic binding for the destructor
#ifndef Simulating_Virtual_Copy 
	virtual Quote *clone() const & { // virtual function to return a dynamically allocated copy of itself // these members use reference qualifiers; see § 13.6.3 (p. 546)
		return new Quote(*this); 
	}

	virtual Quote *clone() && {
		return new Quote(std::move(*this)); //TEST!
	}
#endif // other members as before
private:
	std::string bookNo; // ISBN number of this item
protected:
	double price = 0.0; // normal, undiscounted price
};
#endif