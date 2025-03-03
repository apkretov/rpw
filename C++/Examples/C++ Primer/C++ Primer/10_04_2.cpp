#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "05_06_2.h"
using namespace std;

#ifdef ON
void Operations_on_istream_iterators() {
	ostream_iterator<int> out(cout, " "); //MINE

#ifdef _1
	istream_iterator<int> in_iter(cin); //TEST! //																																				read ints from cin
	istream_iterator<int> eof; // istream ‘‘end’’ iterator
	vector<int> vec; //MINE

	while (in_iter != eof) //TEST!! //																																							while there’s valid input to read
		vec.push_back(*in_iter++); //TEST! //																																					postfix increment reads the stream and returns the old value of the iterator	// we dereference that iterator to get the previous value read from the stream
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE

#elif! _2
	istream_iterator<int> in_iter(cin), eof; // read ints from cin
	vector<int> vec(in_iter, eof); //TEST!! //																																				construct vec from an iterator range
	copy(vec.cbegin(), vec.cend(), out); cout << '\n'; //MINE
#endif
}

void mine1() {
	istream_iterator<string> in(cin), eof;
	copy(in, eof, ostream_iterator<string>(cout, "\n")); //TEST!!
}

void Using_Stream_Iterators_with_the_Algorithms() {
	istream_iterator<int> in(cin), eof;
	cout << accumulate(in, eof, 0) << endl; //TEST!!
}

void Operations_on_ostream_iterators() {
	vector<int> vec = {0, 1, 2, 3, 4}; //MINE
	ostream_iterator<int> out_iter(cout, " ");

	for (auto e : vec)
		*out_iter++ = e; //TEST!! //																																							the assignment writes this element to cout
	cout << endl;

	for (auto e : vec)
		out_iter = e; //TEST!! //																																								the assignment writes this element to cout
	cout << endl;

	copy(vec.begin(), vec.end(), out_iter);
	cout << endl;
}

void Using_Stream_Iterators_with_Class_Types() {
	istream_iterator<Sales_item> item_iter(cin), eof; //item_iter
	ostream_iterator<Sales_item> out_iter(cout, "\n");
	
	Sales_item sum = *item_iter++; //TEST!! //																																					store the first transaction in sum and read the next record
	while (item_iter != eof) {
		if (item_iter->isbn() == sum.isbn()) // if the current transaction (which is stored in item_iter) has the same ISBN
			//ERR sum += *item_iter++; // add it to sum and read the next transaction
			sum.count = sum + *item_iter++; //TEST!! //MINE																																		See int operator+(const Sales_item &item) const;
		else {
			out_iter = sum; //TEST! //																																							write the current sum
			sum = *item_iter++; // read the next transaction
		}
	}
	out_iter = sum; // remember to print the last set of records
}

void mine2() {
#ifdef INPUT_1
	vector<string> v;
	string s;
	while (cin >> s)
		v.push_back(s);

#elif INPUT_2
	istream_iterator<string> in(cin), eof;
	vector<string> v(in, eof);

#elif INPUT_3
	vector<string> v;
	string s;
	auto it = back_inserter(v);
	while (cin >> s)
		it = s;

#elif! INPUT_4
	vector<string> v;
	auto it = back_inserter(v);
	istream_iterator<string> in(cin), eof;
	while (in != eof)
		it = *in++;
#endif

	copy(v.cbegin(), v.cend(), ostream_iterator<string>(cout, " "));
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Operations_on_istream_iterators();
	//mine1();
	//Using_Stream_Iterators_with_the_Algorithms();
	//Operations_on_ostream_iterators();
	//Using_Stream_Iterators_with_Class_Types();
	mine2();

	return 0;
}
#endif

#ifdef EX_10_29

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	ifstream file(argv[1]);
	vector<string> v;
	
	copy(istream_iterator<string>(file), istream_iterator<string>(), back_inserter(v)); //TEST!!
	copy(v.cbegin(), v.cend(), ostream_iterator<string>(cout, " "));
	cout << '\n';

	return 0;
}

#endif

#ifdef EX_10_31

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	istream_iterator<string> in(cin), eof;
	vector<string> v;
	//TEST! copy(in, eof, back_inserter(v));
	
	sort(v.begin(), v.end());
	//TEST! unique_copy(v.cbegin(), v.cend(), ostream_iterator<string>(cout, " "));
	cout << '\n';

	return 0;
}

#endif

bool compareIsbn(const Sales_item &lhs, const Sales_item &rhs) {
	return lhs.isbn() < rhs.isbn();
}

#ifdef EX_10_32_1

#include <map>
#include "../../stdafx.h"

int main(int, char *argv[]) {
	print_file_line();

	vector<Sales_item> v;
	Sales_item sa;
	ostream_iterator<Sales_item>out_it(cout, "\n");
	ifstream in(argv[1]);
	istream_iterator<Sales_item> in_it(in), eof;

	copy(in_it, eof, back_inserter(v));
	cout << "Before sorting:\n";
	copy(v.cbegin(), v.cend(), out_it);
	sort(v.begin(), v.end(), compareIsbn);
	cout << "\nAfter sorting:\n";
	copy(v.cbegin(), v.cend(), out_it);

#ifndef MINE
	map<string, int> isbn;
	vector<int> vi;
	for (const auto &it : v) {
		isbn.insert({it.isbn(), 0});
		vi.push_back(it.count);
	}
	cout << "\nThe unique isbns:\n";
	for_each(isbn.cbegin(), isbn.cend(), [](const pair<string, int> &p) {cout << p.first << '\t'; });

	for (auto &it : isbn) {
		auto pr = equal_range(v.cbegin(), v.cend(), it.first, compareIsbn);
		it.second = accumulate(vi.cbegin() + (pr.first - v.cbegin()), vi.cbegin() + (pr.second - v.cbegin()), 0);
	}	
#elif! CHATGPT // Instead of creating a separate std::vector<int> and copying the counts to it, we directly update the count in the std::map using the += operator.
	map<string, int> isbn;
	for (const auto &it : v) {
		isbn[it.isbn()] += it.count;
	}
#endif

	cout << "\n\nAfter accumulation:\n";
	for_each(isbn.cbegin(), isbn.cend(), [](const pair<string, int> &pr) { cout << pr.first << ' ' << pr.second << '\n'; });

	return 0;
}
#endif

#ifdef EX_10_32_2 // ch10/ex10_32.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch10/ex10_32.cpp
int main() {
	istream_iterator<Sales_item> in_iter(cin), in_eof;
	vector<Sales_item> vec;

	while (in_iter != in_eof)
		vec.push_back(*in_iter++);

	sort(vec.begin(), vec.end(), compareIsbn);

	for (auto beg = vec.cbegin(), end = beg; beg != vec.cend(); beg = end) {
		end = find_if(beg, vec.cend(), [beg](const Sales_item &item) { return item.isbn() != beg->isbn(); });		
		//ERR cout << accumulate(beg, end, Sales_item(beg->isbn())) << endl;
	}
}
#endif

#ifdef EX_10_32_3 // Cpp-Primer-5th-Exercises/ch10/10.32.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch10/10.32.cpp
int process_transaction_v2(istream &in, ostream &out) { //TEST!!
	istream_iterator<Sales_item> i_iter(in), eof;
	vector<Sales_item> trans(i_iter, eof);

	if (trans.empty()) {
		cerr << "No data!" << endl;
		return -1;
	}
	
	//ORIG sort(trans.begin(), trans.end(), compareIsbn_v2);
	sort(trans.begin(), trans.end(), compareIsbn); //MINE
	
	ostream_iterator<Sales_item> o_iter(out, "\n"); // The original version in header use `==` operator, so that only transactions having the same ISBN with the first transaction will be sorted, others will be unsorted. This may not be what we want.
	for (auto bg = trans.begin(), ed = bg; bg != trans.end(); bg = ed) {
		ed = find_if_not(bg, trans.end(), [bg](const Sales_item &i) { return i.isbn() == bg->isbn(); });
		//ERR o_iter = accumulate(bg, ed, Sales_item(bg->isbn()));
		o_iter = *bg; //TEST!! //MINE
	}
	
	return 0;
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	if (argc < 2) {
		cerr << "Usage: 10.32 <input filename> [<output filename>]" << endl;
		return -3;
	}
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Fail to open file: " << argv[1] << endl;
		return -2;
	}
	if (argc >= 3) {
		ofstream out(argv[2], ofstream::app);
		if (!out) {
			cerr << "Fail to open file: " << argv[1] << endl;
			return -2;
		}
		process_transaction_v2(in, out);
	} else
		process_transaction_v2(in, cout);

	return 0;
}
#endif

#ifdef EX_10_32_4
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	ifstream in(argv[1]);
	istream_iterator<Sales_item> it_in(in), eof;
	vector<Sales_item> v(it_in, eof);
	ostream_iterator<Sales_item> out(cout, "\n");
	
	cout << "Before sorting:\n";
	copy(v.cbegin(), v.cend(), out);
	
	sort(v.begin(), v.end(), compareIsbn);
	cout << "\nAfter sorting:\n";
	copy(v.cbegin(), v.cend(), out);

	cout << '\n';
	for (auto beg = v.cbegin(), end = beg; beg != v.cend(); beg = end) {
		end = find_if(beg, v.cend(), [&beg](const Sales_item &it) { return it != *beg; });
		
		decltype(Sales_item::count) total{};
		for (auto it = beg; it != end; ++it) 
			total += it->count;
		cout << "Total for s " << beg->isbn() << " = " << total << '\n';
	}

	return 0;
}
#endif