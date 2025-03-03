#pragma once

#ifndef Equality_Operators

#include <iostream>

#ifndef Suppressing_Implicit_Conversions_Defined_by_Constructors
class Sales_data { //VER12
	friend Sales_data add(const Sales_data &, const Sales_data &); // friend declarations for nonmember Sales_data operations added
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);
#ifndef EX_14_02
	friend std::ostream &operator<<(std::ostream &, const Sales_data &);
	friend std::istream &operator>>(std::istream &, Sales_data &);
	friend Sales_data operator+(const Sales_data &, const Sales_data &);
#endif
#ifndef Equality_Operators
	friend bool operator==(const Sales_data &, const Sales_data &);
	friend bool operator!=(const Sales_data &, const Sales_data &);
#endif
public:
	Sales_data() = default;
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p *n) {}
	explicit Sales_data(const std::string &s) : bookNo(s) {}
	explicit Sales_data(std::istream &);
#ifndef The_Synthesized_Copy_Constructor
	Sales_data(const Sales_data &);
#endif
#ifndef Using_default
	Sales_data &operator=(const Sales_data &sd) = default; //TEST!
#endif
#ifndef EX_14_02
	Sales_data &operator+=(const Sales_data &);
#endif
	std::string isbn() const { // remaining members as before
		return bookNo;
	}

	Sales_data &combine(const Sales_data &); // other members as before

	double avg_price() const { //MINE
		return units_sold ? revenue / units_sold : 0;
	}
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
#endif