#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef Suppressing_Implicit_Conversions_Defined_by_Constructors
class Sales_data { //VER10
	friend Sales_data add(const Sales_data &, const Sales_data &); // friend declarations for nonmember Sales_data operations added
	friend istream &read(istream &, Sales_data &);
	friend ostream &print(ostream &, const Sales_data &);

public:
	Sales_data() = default;
	Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p *n) {}
	explicit Sales_data(const string &s) : bookNo(s) {}
	explicit Sales_data(istream &);
#ifndef The_Synthesized_Copy_Constructor
	Sales_data(const Sales_data &);
#endif
#ifndef Using_default
	Sales_data &operator=(const Sales_data &sd) = default; //TEST!
#endif
	string isbn() const { // remaining members as before
		return bookNo;
	}

	Sales_data &combine(const Sales_data &); // other members as before

	double avg_price() const { //MINE
		return units_sold ? revenue / units_sold : 0;
	}
private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif