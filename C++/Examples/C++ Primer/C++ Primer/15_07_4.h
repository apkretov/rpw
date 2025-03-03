#pragma once

#ifndef Inherited_Constructors
class Bulk_quote : public Disc_quote { //VER5
public:
	using Disc_quote::Disc_quote; //TEST!! // inherit Disc_quote’s constructors
	double net_price(std::size_t) const;
};
#endif

#ifndef MINE
double Bulk_quote::net_price(size_t n) const {
	return n;
}
#endif