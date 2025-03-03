#pragma once

#ifndef A_Derived_Class_Constructor_Initializes_Its_Direct_Base_Class_Only
class Bulk_quote : public Disc_quote { //VER4.1 // the discount kicks in when a specified number of copies of the same book are sold // the discount is expressed as a fraction to use to reduce the normal price
public:
#ifndef EX_15_26
	Bulk_quote();
	Bulk_quote(const std::string &book, double price, std::size_t qty, double disc);
	Bulk_quote(const Bulk_quote &);
	Bulk_quote(Bulk_quote &&) noexcept;
	Bulk_quote &operator=(const Bulk_quote &);
	Bulk_quote &operator=(Bulk_quote &&) noexcept;
	virtual ~Bulk_quote() final;
	double net_price(std::size_t) const final;
#endif
};
#endif

#ifndef EX_15_26
Bulk_quote::Bulk_quote() {
#ifdef LOG
	std::cout << "Bulk_quote constructor.\n";
#endif
}

Bulk_quote::Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) {
#ifdef LOG
	std::cout << "Bulk_quote constructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

Bulk_quote::Bulk_quote(const Bulk_quote &b) : Disc_quote(b) {
#ifdef LOG
	std::cout << "Bulk_quote copy constructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

Bulk_quote::Bulk_quote(Bulk_quote &&b) noexcept : Disc_quote(std::move(b)) {
#ifdef LOG
	std::cout << "Bulk_quote move constructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

Bulk_quote &Bulk_quote::operator=(const Bulk_quote &b) {
	if (&b != this)
		Disc_quote::operator=(b);
#ifdef LOG
	std::cout << "Bulk_quote copy-assignment operator: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
	return *this;
}

Bulk_quote &Bulk_quote::operator=(Bulk_quote &&b) noexcept {
	if (&b != this)
		Disc_quote::operator=(std::move(b));
#ifdef LOG
	std::cout << "Bulk_quote move-assignment operator: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
	return *this;
}

Bulk_quote::~Bulk_quote() {
#ifdef LOG
	std::cout << "Bulk_quote destructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

double Bulk_quote::net_price(size_t n) const {
#ifdef LOG
	std::cout << "Bulk_quote net_price: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
	return 0;
}
#endif