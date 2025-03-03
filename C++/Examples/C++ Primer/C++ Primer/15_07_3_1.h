#pragma once

#include <iostream>

#define LOG

#ifndef Defining_a_Base_Class
class Quote { //VER3.1
public:
#ifndef EX_15_26
	Quote();
	Quote(const std::string &book, double sales_price);
	Quote(const Quote &);
	Quote(Quote &&) noexcept;
	Quote &operator=(const Quote &);
	Quote &operator=(Quote &&) noexcept;
	virtual ~Quote();
	void setBookNo(const std::string &);
	void setBookNo(std::string &&);
	virtual double net_price(std::size_t n);
#endif
	std::string isbn() const {
		return bookNo;
	}

private:
	std::string bookNo; // ISBN number of this item
protected:
	double price = 0.0; // normal, undiscounted price
};
#endif

#ifndef EX_15_26
Quote::Quote() {
#ifdef LOG
	std::cout << "Quote constructor.\n";
#endif
}

Quote::Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {
#ifdef LOG
	std::cout << "Quote constructor: isbn() = " << isbn() << "  price = " << price << '\n';
#endif
}

Quote::Quote(const Quote &q) : bookNo(q.bookNo), price(q.price) {
#ifdef LOG
	std::cout << "Quote copy constructor: isbn() = " << isbn() << "  price = " << price << '\n';
#endif
}

Quote::Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(q.price) {
#ifdef LOG
	std::cout << "Quote move constructor: isbn() = " << isbn() << "  price = " << price << '\n';
#endif
}

Quote &Quote::operator=(const Quote &rhs) {
	if (&rhs != this) {
		bookNo = rhs.bookNo;
		price = rhs.price;
	}
#ifdef LOG
	std::cout << "Quote copy-assignment operator: isbn() = " << isbn() << "  price = " << price << '\n';
#endif
	return *this;
}

Quote &Quote::operator=(Quote &&rhs) noexcept {
	if (&rhs != this) {
		bookNo = std::move(rhs.bookNo);
		price = rhs.price;
	}
#ifdef LOG
	std::cout << "Quote move-assignment operator: isbn() = " << isbn() << "  price = " << price << '\n';
#endif
	return *this;
}

void Quote::setBookNo(const std::string &bNo) { 
	bookNo = bNo; 
#ifdef LOG
	std::cout << "setBookNo(const string &): bookNo = " << bookNo << '\n';
#endif
}

void Quote::setBookNo(std::string &&bNo) { 
	bookNo = std::move(bNo); 
#ifdef LOG
	std::cout << "setBookNo(string &&): bookNo = " << bookNo << '\n';
#endif
}

Quote::~Quote() {
#ifdef LOG
	std::cout << "Quote destructor: isbn() = " << isbn() << "  price = " << price << "\n\n";
#endif
}

double Quote::net_price(std::size_t n) {
#ifdef LOG
	std::cout << "Quote net_price: isbn() = " << isbn() << "  price = " << price << '\n';
#endif
	return n * price;
}
#endif