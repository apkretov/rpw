#pragma once

#include "15_02_1.h"

#ifndef Defining_a_Derived_Class
class Bulk_quote : public Quote { //VER3 // Bulk_quote inherits from Quote
public: //MINE
	Bulk_quote() = default;
#ifndef Derived_Class_Constructors
	Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) { }
	// as before
#endif
	double net_price(std::size_t) const override; // overrides the base version in order to implement the bulk purchase discount policy
private:
	std::size_t min_qty = 0; // minimum purchase for the discount to apply
	double discount = 0.0; // fractional discount to apply
};
#endif

#ifndef Using_Members_of_the_Base_Class_from_the_Derived_Class
double Bulk_quote::net_price(size_t cnt) const { // if the specified number of items are purchased, use the discounted price
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	else
		return cnt * price;
}
#endif