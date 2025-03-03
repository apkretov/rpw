#pragma once

#include "15_02_1.h"

#ifndef Defining_a_Derived_Class
class Bulk_quote : public Quote { //VER2 // Bulk_quote inherits from Quote
public: //MINE
	Bulk_quote() = default;
	Bulk_quote(const std::string &, double, std::size_t, double);
	double net_price(std::size_t) const override; // overrides the base version in order to implement the bulk purchase discount policy
private:
	std::size_t min_qty = 0; // minimum purchase for the discount to apply
	double discount = 0.0; // fractional discount to apply
};
#endif
