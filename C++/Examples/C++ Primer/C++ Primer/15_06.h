#pragma once

#include <string>
#include <utility>
using namespace std;

#ifndef Pure_Virtual_Functions
class Disc_quote : public Quote { //VER2 // class to hold the discount rate and quantity // derived classes will implement pricing strategies using these data
public:
	Disc_quote() = default;
	Disc_quote(const string &book, double price, size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(size_t) const = 0;
#ifndef Name_Lookup_Happens_at_Compile_Time
	pair<size_t, double> discount_policy() const {
		return {quantity, discount};
	} // other members as before
#endif 
protected:
	size_t quantity = 0; // purchase size for the discount to apply
	double discount = 0.0; // fractional discount to apply
};
#endif