#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Exception Classes for a Bookstore Application
class out_of_stock : public runtime_error { // hypothetical exception classes for a bookstore application
public:
	explicit out_of_stock(const string &s) : runtime_error(s) {}
};

class isbn_mismatch : public logic_error { //TEST
public:
	explicit isbn_mismatch(const string &s) : logic_error(s) {}
	isbn_mismatch(const string &s, const string &lhs, const string &rhs) : logic_error(s), left(lhs), right(rhs) {}
	const string left, right;
};
#pragma endregion

#pragma region Using Our Own Exception Types

#include "14_01.h"

Sales_data &Sales_data::operator+=(const Sales_data &rhs) { // throws an exception if both objects do not refer to the same book
	if (isbn() != rhs.isbn())
		throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn()); //TEST
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
#pragma endregion

#ifdef ON

void Using_Our_Own_Exception_Types() {
	Sales_data item1, item2, sum; // use the hypothetical bookstore exceptions
	while (cin >> item1 >> item2) { // read two transactions
		try {
			sum = item1 + item2; // calculate their sum
			// use sum
		}
		catch (const isbn_mismatch &e) { //TEST
			cerr << e.what() << ": left isbn(" << e.left << ") right isbn(" << e.right << ")" << endl;
		}
	}
}

int main() {
	print_file_line();

	Using_Our_Own_Exception_Types();

	return 0;
}
#endif
