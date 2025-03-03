#pragma once

#pragma region MINE

#include <iostream>
#include <vector>
using std::vector;
using std::cout;

using stores_sales = vector<vector<Sales_data>>;
using size_type = vector<Sales_data>::size_type;

void compileStoreSales(stores_sales &files) {
	auto triple = [](vector<Sales_data> &v, const Sales_data &sd) {
		for (size_t i = 0; i < 3; ++i)
			v.push_back(sd);
		};

	for (size_t i = 0; i < 3; ++i) {
		vector<Sales_data> bookSales;
		triple(bookSales, Sales_data("aaa", 1, 10));
		triple(bookSales, Sales_data("bbb", 2, 20));
		triple(bookSales, Sales_data("ccc", 3, 30));
		files.emplace_back(bookSales);
	}
}

void printStoreSales(const stores_sales &files) {
	cout << "Stores sales:\n";
	for (size_type store_id{}; const auto & store : files) {
		cout << "\nStore " << store_id << ":\n";
		for (const auto &book_sales : store)
			cout << book_sales << '\n';
		++store_id;
	}
	cout << '\n';
}
#pragma endregion
