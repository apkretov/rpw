#pragma once

#include "15_02_1.h"

#ifndef Pure_Virtual_Functions
class Disc_quote : public Quote { //VER1 // class to hold the discount rate and quantity // derived classes will implement pricing strategies using these data
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}
	double net_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0; // purchase size for the discount to apply
	double discount = 0.0; // fractional discount to apply
};
#endif