#pragma once

#include <iostream>

#ifndef Defining_the_Members_of_Basket
double Basket::total_receipt(std::ostream &os) const {
	double sum = 0.0; // holds the running total

	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) { // iter refers to the first element in a batch of elements with the same ISBN // upper_bound returns an iterator to the element just past the end of that batch
		sum += print_total(os, **iter, items.count(*iter)); // we know there’s at least one element with this key in the Basket	// print the line item for this book
	}
	
	os << "Total Sale: " << sum << std::endl; // print the final overall total
	return sum;
}
#endif
