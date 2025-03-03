#ifdef ON

#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#include "07_05_4.h"

void Using_an_Unordered_Container() {
	unordered_map<string, size_t> word_count; // count occurrences, but the words won’t be in alphabetical order
	string word;

	while (cin >> word)
		++word_count[word]; // fetch and increment the counter for word

	for (const auto &w : word_count) // for each element in the map
		cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl; // print the results
}

#ifndef  Requirements_on_Key_Type_for_Unordered_Containers

size_t hasher(const Sales_data &sd) {
	return hash<string>()(sd.isbn()); //TEST!
}

bool eqOp(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() == rhs.isbn();
}

using SD_multiset = unordered_multiset<Sales_data, decltype(hasher) *, decltype(eqOp) *>; //TEST!
SD_multiset bookstore(42, hasher, eqOp); // arguments are the bucket size and pointers to the hash function and equality operator

//OFF unordered_set<Foo, decltype(FooHash) *> fooSet(10, FooHash); // use FooHash to generate the hash code; Foo must have an == operator
#endif

void mine() {
	bookstore.emplace("book 2", 20, 200);
	bookstore.emplace("book 1", 10, 100);

	for (const auto &i : bookstore)
		print(cout, i) << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	//Using_an_Unordered_Container();
	mine();
	
	return 0;
}
#endif
