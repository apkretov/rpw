#ifdef ON

#include <iostream>
#include <format>
#include <list>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void Defining_and_Initializing_tuples() {
	tuple<size_t, size_t, size_t> threeD; //TEST! //																												all three members set to 0
	tuple<string, vector<double>, int, list<int>> someVal("constants", {3.14, 2.718}, 42, {0,1,2,3,4,5});

	{
		//TEST! tuple<size_t, size_t, size_t> threeD = {1,2,3}; //																									error
		tuple<size_t, size_t, size_t> threeD{1,2,3}; // ok
	}

	auto item = make_tuple("0-999-78345-X", 3, 20.00); //TEST //																									tuple that represents a bookstore transaction: ISBN, count, price per book

#pragma region Accessing the Members of a tuple
	auto book = get<0>(item); //TEST //																																returns the first member of item // returns the first member of item
	auto cnt = get<1>(item); // returns the second member of item
	auto price = get<2>(item) / cnt; // returns the last member of item
	get<2>(item) *= 0.8; // apply 20% discount

	//MINE
	cout << "book = " << book << '\n';
	cout << "cnt = " << cnt << '\n';
	cout << "price = " << price << '\n';

	{
		typedef decltype(item) trans; // trans is the type of item
		size_t sz = tuple_size<trans>::value; //TEST! //																												returns 3 // returns the number of members in object’s of type trans
		tuple_element<1, trans>::type cnt = get<1>(item); //TEST! //																									cnt is an int // cnt has the same type as the second member in item
		auto cnt_mine = get<1>(item); //TEST //MINE

		//MINE
		cout << "\nsz = " << sz;
		cout << "\ncnt = " << typeid(cnt).name();
		cout << "\ncnt_mine = " << cnt_mine << '\n';
	}
#pragma endregion
}

void Relational_and_Equality_Operators() {
	tuple<string, string> duo("1", "2");
	tuple<size_t, size_t> twoD(1, 2);
	//TEST bool b = (duo == twoD); // error: can’t compare a size_t and a string

	tuple<size_t, size_t, size_t> threeD(1, 2, 3);
	//TEST b = (twoD < threeD); // error: differing number of members

	tuple<size_t, size_t> origin(0, 0);
	bool b = (origin < twoD); //TEST // ok: b is true
	cout << format("(origin < twoD) = {}\n", b); //MINE
}

int main() {
	print_file_line();

	//Defining_and_Initializing_tuples();
	Relational_and_Equality_Operators();
}
#endif

#ifdef EX_17_01

#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() {
	print_file_line();

	auto t = make_tuple(10, 20, 30);
	cout << "get<0>(t) = " << get<0>(t) << '\n';
	cout << "get<1>(t) = " << get<1>(t) << '\n';
	cout << "get<2>(t) = " << get<2>(t) << '\n';

}
#endif

#ifdef EX_17_02

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

int main() {
	print_file_line();

	tuple<string, vector<string>, pair<string, int>> t{"one", {"two", "three"}, {"four", 5}};
	cout << "get<0>(t) = " << get<0>(t) << '\n';

	auto v = get<1>(t);
	cout << "get<1>(t) = ";
	ranges::copy(v, ostream_iterator<string>(cout, " "));

	auto const &[first, second] = get<2>(t);
	cout << "\nget<2>(t) = " << first << " " << second << '\n';
}
#endif

#ifdef EX_17_03

#include <iostream>
#include <fstream>
//OFF #include <vld.h>
#include "../../stdafx.h"
#include "17_01_1.h"
using namespace std;
using namespace How_Values_Are_Returned;

#pragma region EX_17_03
ostream &print(ostream &os, const TextQuery::QueryResult &qr) {
	const auto &[sought, lines, file] = qr;
	os << sought << " occurs " << lines->size() << " " << make_plural(lines->size(), "time", "s") << endl; // if the word was found, print the count and all occurrences
	for (auto num : *lines) // print each line in which the word appeared // for every element in the std::set
		os << "\t(line " << num + 1 << ") " << *(file->begin() + num) << endl; // don’t confound the user with text lines starting at 0
	return os;
}
#pragma endregion

#ifndef Using_the_TextQuery_Class
void runQueries(ifstream &infile) { // infile is an ifstream that is the file we want to query
	TextQuery tq(infile); // store the file and build the query map

	while (true) { 	// iterate with the user: prompt for a word to find and print results
		cout << "enter word to look for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q") // stop if we hit end-of-file on the input or if a ’q’ is entered
			break;
		print(cout, tq.query(s)) << endl; // run the query and print the results
	}
}
#endif

int main(int, char *argv[]) {
	using namespace std;
	print_file_line();

	ifstream in(argv[1]);

	runQueries(in);

	return 0;
}
#endif
