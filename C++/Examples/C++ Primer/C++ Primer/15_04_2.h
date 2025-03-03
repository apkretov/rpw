#pragma once

#include <string>
using std::string;

#ifndef A_Derived_Class_Constructor_Initializes_Its_Direct_Base_Class_Only
class Bulk_quote : public Disc_quote { //VER4 // the discount kicks in when a specified number of copies of the same book are sold // the discount is expressed as a fraction to use to reduce the normal price
public:
	Bulk_quote() = default;
	Bulk_quote(const string &book, double price, size_t qty, double disc) : Disc_quote(book, price, qty, disc) {}
	double net_price(size_t) const override; // overrides the base version to implement the bulk purchase discount policy
};
#endif

#ifndef MINE
double Bulk_quote::net_price(size_t n) const {
	return 0;
}
#endif