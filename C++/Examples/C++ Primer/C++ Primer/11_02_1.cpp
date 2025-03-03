#ifdef ON

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

void Defining_an_Associative_Container() {
	map<string, size_t> word_count; // empty
	set<string> exclude = {"the", "but", "and", "or", "an", "a", // list initialization
						   "The", "But", "And", "Or", "An", "A"};
	map<string, string> authors = {{"Joyce", "James"}, // three elements; authors maps last name to first
								   {"Austen", "Jane"},
								   {"Dickens", "Charles"}};
}

void Initializing_a_multimap_or_multiset() { 
	vector<int> ivec; // define a vector with 20 elements, holding two copies of each number from 0 to 9
	for (vector<int>::size_type i = 0; i != 10; ++i) {
		ivec.push_back(i);
		ivec.push_back(i); // duplicate copies of each number
	}
	
	set<int> iset(ivec.cbegin(), ivec.cend()); // iset holds unique elements from ivec; miset holds all 20 elements
	multiset<int> miset(ivec.cbegin(), ivec.cend());
	cout << ivec.size() << endl; // prints 20
	cout << iset.size() << endl; // prints 10
	cout << miset.size() << endl; // prints 20
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	Initializing_a_multimap_or_multiset();

	return 0;
}

#endif
