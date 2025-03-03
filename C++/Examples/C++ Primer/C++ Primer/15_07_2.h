#pragma once

#include <string>
using namespace std;

#ifndef Defining_a_Base_Class
class Quote { //VER3
public:
	Quote() = default; // = default see § 7.1.4 (p. 264)
	Quote(const string &book, double sales_price) : bookNo(book), price(sales_price) {}
#ifndef Move_Operations_and_Inheritance //TEST!
	Quote(const Quote &) = default; //TEST!!																												// memberwise copy //MINE: Page 625: Once it defines its move operations, it must also explicitly define the copy versions as well (§ 13.6.2, p. 539)
	Quote(Quote &&) = default; //TEST!!																														// memberwise copy //MINE: Page 625: most base classes define a virtual destructor. As a result, by default, base classes generally do not get synthesized move operations.
	Quote &operator=(const Quote &) = default; //TEST!!																										// copy assign
	Quote &operator=(Quote &&) = default; //TEST!!																											// move assign
#endif // other members as before

	string isbn() const {
		return bookNo;
	}

	virtual double net_price(size_t n) const { // returns the total sales price for the specified number of items // derived classes will override and apply different discount algorithms
		return n * price;
	}

	virtual ~Quote() = default; // dynamic binding for the destructor
private:
	string bookNo; // ISBN number of this item
protected:
	double price = 0.0; // normal, undiscounted price
};
#endif