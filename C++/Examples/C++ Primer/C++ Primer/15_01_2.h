#pragma once

#include <iostream>

#ifndef Dynamic_Binding
double print_total(std::ostream &os, const Quote &item, size_t n) { // calculate and print the price for the given number of copies, applying any discounts
	double ret = item.net_price(n); // depending on the type of the object bound to the item parameter // calls either Quote::net_price or Bulk_quote::net_price
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl; // calls Quote::isbn
	return ret;
}
#endif
