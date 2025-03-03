#pragma once

#ifndef Inherited_Constructors
class Bulk_quote : public Disc_quote { //VER6
public:
	using Disc_quote::Disc_quote; // inherit Disc_quote’s constructors
	double net_price(std::size_t) const;
#ifndef Simulating_Virtual_Copy 
	Bulk_quote *clone() const & { 
		return new Bulk_quote(*this); 
	}
	
	Bulk_quote *clone() && {
		return new Bulk_quote(std::move(*this));
	}
#endif // other members as before
};
#endif

#ifndef MINE
double Bulk_quote::net_price(size_t n) const {
	return 0;
}
#endif