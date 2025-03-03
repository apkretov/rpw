#ifdef ON

#include <iostream>
#include <map>
#include <set>
using namespace std;

void Associative_Container_Iterators() {
	map<string, int> word_count {{"a", 0}}; //MINE
	auto map_it = word_count.begin(); // get an iterator to an element in word_count
	// *map_it is a reference to a pair<const string, size_t> object
	
	cout << map_it->first; // prints the key for this element
	cout << " " << map_it->second; // prints the value of the element
	//TEST! map_it->first = "new key"; //																																								error: key is const
	++map_it->second; //																																												ok: we can change the value through an iterator
}

void Iterators_for_sets_Are_const() {
	set<int> iset = {0,1,2,3,4,5,6,7,8,9};

	set<int>::iterator set_it = iset.begin();
	if (set_it != iset.end()) {
		//TEST! *set_it = 42; //																																										error: keys in a set are read-only
		cout << *set_it << endl; //																																										ok: can read the key
	}
}

void Iterating_across_an_Associative_Container() {
	map<string, int> word_count;
	string s;

	while (cin >> s)
		++word_count[s];
	
	for (const auto &i : word_count)
		cout << i.first << '\t' << i.second << '\n';
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Associative_Container_Iterators();
	Iterating_across_an_Associative_Container();

	return 0;
}

#endif

#ifdef EX_11_17

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	multiset<string> c{"A", "B", "C", "D"};
	vector<string> v{"a", "b", "c", "d"};

	//TEST! copy(v.cbegin(), v.cend(), inserter(c, c.end())); 
	//TEST! copy(v.cbegin(), v.cend(), back_inserter(c)); 
	//TEST! copy(c.cbegin(), c.cend(), inserter(v, v.end())); 
	//TEST! copy(c.cbegin(), c.cend(), inserter(v, v.begin())); //MINE
	//TEST! copy(c.cbegin(), c.cend(), back_inserter(v)); 

	return 0;
}

#endif

#ifdef EX_11_18

#include <iostream>
#include <map>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	map<string, int> word_count;
	map<string, int>::const_iterator it = word_count.cbegin();

	return 0;
}

#endif
