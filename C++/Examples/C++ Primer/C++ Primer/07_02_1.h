#ifdef Friends

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

class Sales_data { //VER05
	friend Sales_data add(const Sales_data &, const Sales_data &); // friend declarations for nonmember Sales_data operations added
	friend std::istream &read(std::istream &, Sales_data &);
	friend std::ostream &print(std::ostream &, const Sales_data &);
public: // other members and access specifiers as before
	Sales_data() = default;
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p *n) {
	}
	Sales_data(const std::string &s) : bookNo(s) {}
	Sales_data(std::istream &);
	std::string isbn() const { return bookNo; }
	Sales_data &combine(const Sales_data &);
	double avg_price() const { //MINE
		return units_sold ? revenue / units_sold : 0;
	}
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

/*ORIG: Many compilers do not enforce the rule that friend functions must be declared outside the class before they can be used.
Sales_data add(const Sales_data &, const Sales_data &); // declarations for nonmember parts of the Sales_data interface
std::istream &read(std::istream &, Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
*/

#endif
#endif

