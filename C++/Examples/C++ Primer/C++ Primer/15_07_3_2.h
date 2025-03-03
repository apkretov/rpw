#pragma once

#ifndef Pure_Virtual_Functions
class Disc_quote : public Quote { //VER2.1 // class to hold the discount rate and quantity // derived classes will implement pricing strategies using these data
public:
#ifndef EX_15_26
	Disc_quote();
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc);
	Disc_quote(const Disc_quote &);
	Disc_quote(Disc_quote &&) noexcept;
	Disc_quote &operator=(const Disc_quote &);
	Disc_quote &operator=(Disc_quote &&) noexcept;
	virtual ~Disc_quote() override;
	virtual double net_price(std::size_t) const = 0;
#endif
#ifndef Name_Lookup_Happens_at_Compile_Time
	std::pair<size_t, double> discount_policy() const {
		return {quantity, discount};
	} // other members as before
#endif 
protected:
	std::size_t quantity = 0; // purchase size for the discount to apply
	double discount = 0.0; // fractional discount to apply
};
#endif

#ifndef EX_15_26
Disc_quote::Disc_quote() {
#ifdef LOG
	std::cout << "Disc_quote constructor.\n";
#endif
}

Disc_quote::Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {
#ifdef LOG
	std::cout << "Disc_quote constructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

Disc_quote::Disc_quote(const Disc_quote &d) : Quote(d), quantity(d.quantity), discount(d.discount) {
#ifdef LOG
	std::cout << "Disc_quote copy constructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

Disc_quote::Disc_quote(Disc_quote &&d) noexcept : Quote(std::move(d)), quantity(d.quantity), discount(d.discount) {
#ifdef LOG
	std::cout << "Disc_quote move constructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}

Disc_quote &Disc_quote::operator=(const Disc_quote &d) {
	if (&d != this) {
		Quote::operator=(d);
		quantity = d.quantity;
		discount = d.discount;
	}
#ifdef LOG
	std::cout << "Disc_quote copy-assingment operator: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
	return *this;
}

Disc_quote &Disc_quote::operator=(Disc_quote &&d) noexcept {
	if (&d != this) {
		Quote::operator=(std::move(d));
		quantity = d.quantity;
		discount = d.discount;
	}
#ifdef LOG
	std::cout << "Disc_quote move-assingment operator: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
	return *this;
}

Disc_quote::~Disc_quote() {
#ifdef LOG
	std::cout << "Disc_quote desctructor: isbn() = " << isbn() << "  price = " << Quote::price << "  quantity = " << quantity << "  discount = " << discount << '\n';
#endif
}
#endif