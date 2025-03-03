#if 0

#include <iostream>
#include "../../stdafx.h"
using namespace std;

struct Date {
	int year;
	string month;
	int day;
};

ostream &operator<<(ostream &out, const Date &d) { //MINE
	out << d.year << ' ' << d.month << ' ' << d.day;
	return out;
}

bool operator<(const Date &lhs, const Date &rhs) {
	tuple<const int &, const string &, const int &> lhs_key = tie(lhs.year, lhs.month, lhs.day); 
	auto rhs_key = tie(rhs.year, rhs.month, rhs.day); //TEST Compare: auto rhs_key = make_tuple(rhs.year, rhs.month, rhs.day);
	return lhs_key < rhs_key; //TEST!
}

int main() {
	Date d2{2017, "June", 8};
	Date d1{2017, "January", 26};

	cout << "d1 = " << d1 << '\n';
	cout << "d2 = " << d2 << '\n';
	cout << "(d1 < d2) = " << boolalpha << (d1 < d2) << '\n';
}
#endif
