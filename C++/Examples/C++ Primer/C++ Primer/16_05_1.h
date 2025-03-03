#pragma once

#ifndef Equality_Operators

#include <iostream>

#pragma region Class Template Specializations
template <class T> 
class std::hash; // needed for the friend declaration
#pragma endregion

#ifndef Suppressing_Implicit_Conversions_Defined_by_Constructors
class Sales_data { //VER13
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
#pragma region Class Template Specializations
	friend class std::hash<Sales_data>;	// other members as before
#pragma endregion
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
private: // The private access changed to public.
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif
#endif

#pragma region Class Template Specializations
namespace std { //TEST! //																																		open the std namespace so we can specialize std::hash
	template <> // we’re defining a specialization with
	struct hash<Sales_data> { // the template parameter of Sales_data
		typedef size_t result_type; // the type used to hash an unordered container must define these types
		typedef Sales_data argument_type; // by default, this type needs ==
		size_t operator()(const Sales_data &s) const;
	}; // our class uses synthesized copy control and default constructor

	size_t hash<Sales_data>::operator()(const Sales_data &s) const {
		return hash<string>()(s.bookNo) ^ //TEST!
			hash<unsigned>()(s.units_sold) ^
			hash<double>()(s.revenue);
	}
} // close the std namespace; note: no semicolon after the close curly
#pragma endregion