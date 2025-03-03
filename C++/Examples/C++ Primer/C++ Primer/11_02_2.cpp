#include <iostream>
#include <map>
#include <functional>
using namespace std;
#include "07_05_4.h"

#ifndef Using_a_Comparison_Function_for_the_Key_Type
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() < rhs.isbn();
}

#ifdef ERR 
//ORIG multimap<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn); //TEST!
multimap<Sales_data, bool(*)(const Sales_data &, const Sales_data &)> bookstore(compareIsbn);
multimap<Sales_data, function<bool(const Sales_data &, const Sales_data &)>> bookstore(compareIsbn);
multimap<Sales_data, bool(*)(const Sales_data &, const Sales_data &)> bookstore([](const auto &lhs, const auto &rhs) { return lhs.isbn() < rhs.isbn(); });
multimap<Sales_data, bool(*)(const Sales_data &, const Sales_data &)> bookstore([](const Sales_data &lhs, const Sales_data &rhs) { return lhs.isbn() < rhs.isbn(); });
#endif
#endif

#ifdef ON
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}
#endif
