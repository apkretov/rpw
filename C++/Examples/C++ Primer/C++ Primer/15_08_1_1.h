#pragma once

#include <memory>
#include <set>
#include "15_08_1_3.h"
#include "15_06.h"
#include "15_08_1_4.h"
#include "15_01_2.h"

#ifndef Writing_a_Basket_Class
class Basket { //VER1
public: // Basket uses synthesized default constructor and copy-control members
	void add_item(const std::shared_ptr<Quote> &sale) {
		items.insert(sale);
	}

	double total_receipt(std::ostream &) const; // prints the total price for each book and the overall total for all items in the basket
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) { // function to compare shared_ptrs needed by the multiset member
		return lhs->isbn() < rhs->isbn();
	}

	std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare}; // multiset to hold multiple quotes, ordered by the compare member
};
#endif