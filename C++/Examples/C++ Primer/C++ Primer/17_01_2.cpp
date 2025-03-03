#ifdef ON

#include <algorithm>
#include <iostream>
#include <numeric>
#include "../../stdafx.h"
#include "16_05_1.h"
#include "17_01_2.h"
using namespace std;

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs); //MINE

#pragma region A Function That Returns a tuple
typedef tuple<vector<Sales_data>::size_type, vector<Sales_data>::const_iterator, vector<Sales_data>::const_iterator> matches; // matches has three members: an index of a store and iterators into that store’s vector

vector<matches> findBook(const vector<vector<Sales_data>> &files, const string &book) { // files holds the transactions for every store // findBook returns a vector with an entry for each store that sold the given book
	vector<matches> ret; // initially empty
	for (auto it = files.cbegin(); it != files.cend(); ++it) { // for each store find the range of matching books, if any
		//ORIG auto found = equal_range(it->cbegin(), it->cend(), book, compareIsbn); // find the range of Sales_data that have the same ISBN
		auto found = equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn); //MINE
		if (found.first != found.second) // this store had sales
			ret.push_back(make_tuple(it - files.cbegin(), found.first, found.second)); // remember the index of this store and the matching range
	}
	return ret; // empty if no matches found
}
#pragma endregion

#pragma region Using a tuple Returned by a Function
void reportResults(istream &in, ostream &os, const vector<vector<Sales_data>> &files) {
	auto prompt = []() { cout << "Enter ISBN: "; }; //MINE
	prompt(); //MINE
	string s; // book to look for
	while (in >> s) {
		auto trans = findBook(files, s); // stores that sold this book
		if (trans.empty()) {
			cout << s << " not found in any stores" << endl;
			prompt(); //MINE
			continue; // get the next book to look for
		}
		for (const auto &store : trans) // for every store with a sale
			os << "store " << get<0>(store) << " sales: " << accumulate(get<1>(store), get<2>(store), Sales_data(s)) << endl; // get<n> returns the specified member from the tuple in store
		prompt(); //MINE
	}
}
#pragma endregion

int main() {
	print_file_line();

	//MINE
	stores_sales files;
	compileStoreSales(files);
	printStoreSales(files);
	reportResults(cin, cout, files);
}
#endif

#ifdef EX_17_05

#include <iostream>
#include <algorithm>
#include <numeric>
#include "16_05_1.h"
#include "../../stdafx.h"
#include "17_01_2.h"
using namespace std;

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs); //MINE

#pragma region EX_17_05
using matches = pair<size_type, pair<vector<Sales_data>::const_iterator, vector<Sales_data>::const_iterator>>; // matches has three members: an index of a store and iterators into that store’s vector  
#pragma endregion

#pragma region A Function That Returns a tuple
#pragma region EX_17_05
vector<matches> findBook(const stores_sales &files, const string &book) { // files holds the transactions for every store // findBook returns a vector with an entry for each store that sold the given book
	vector<matches> ret; // initially empty
	for (size_type store_id{}; const auto & store_sales : files) { // for each store find the range of matching books, if any
		auto [found_beg, found_end] = ranges::equal_range(store_sales, Sales_data(book), compareIsbn); // find the range of Sales_data that have the same ISBN
		if (found_beg != found_end) {// this store had sales
			ret.emplace_back(store_id, make_pair(found_beg, found_end)); // remember the index of this store and the matching range
			store_id++;
		}
#pragma endregion
	}
	return ret; // empty if no matches found
}
#pragma endregion

#pragma region Using a tuple Returned by a Function
#pragma region EX_17_05
void reportResults(istream &in, ostream &os, const stores_sales &files) {
#pragma endregion
	auto prompt = []() { cout << "Enter ISBN: "; }; //MINE
	prompt(); //MINE
	string s; // book to look for
	while (in >> s) {
		auto trans = findBook(files, s); // stores that sold this book
		if (trans.empty()) {
			cout << s << " not found in any stores" << endl;
			prompt(); //MINE
			continue; // get the next book to look for
		}
#pragma region EX_17_05
		for (const auto &[store_id, found] : trans) { // for every store with a sale
			os << "store " << store_id << " sales: " << accumulate(found.first, found.second, Sales_data(s)) << '\n';
		}
#pragma endregion
		prompt(); //MINE
	}
}
#pragma endregion

int main() {
	print_file_line();

	//MINE
	stores_sales files;
	compileStoreSales(files);
	printStoreSales(files);
	reportResults(cin, cout, files);
}
#endif
