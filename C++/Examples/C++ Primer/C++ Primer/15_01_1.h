#pragma once

#include <string>
#include <iostream>

#ifndef Inheritance
class Quote { //VER1
public:
	std::string isbn() const;
	virtual double net_price(std::size_t n) const;
};

class Bulk_quote : public Quote { //VER1 // Bulk_quote inherits from Quote
public:
	double net_price(std::size_t) const override;
};
#endif

#ifndef MINE
std::string Quote::isbn() const {
	std::cout << "Quote::isbn()\n";
	return std::string();
}

double Quote::net_price(size_t n) const {
	std::cout << "Quote::net_price(std::size_t n)\n";
	return 0;
}

double Bulk_quote::net_price(size_t n) const {
	std::cout << "Bulk_quote::net_price(std::size_t n)\n";
	return 0;
}
#endif
