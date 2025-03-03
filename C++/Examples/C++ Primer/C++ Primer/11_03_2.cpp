#ifdef ON

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void Adding_Elements() {
	vector<int> ivec = {2,4,6,8,2,4,6,8}; // ivec has eight elements
	set<int> set2; // empty set
	
	set2.insert(ivec.cbegin(), ivec.cend()); // set2 has four elements
	set2.insert({1,3,5,7,1,3,5,7}); // set2 now has eight elements
}

void Adding_Elements_to_a_map() {
	//MINE
	map<string, size_t> word_count;
	string word;

	word_count.insert({word, 1}); // four ways to add word to word_count
	word_count.insert(make_pair(word, 1));
	word_count.insert(pair<string, size_t>(word, 1));
	//TEST! word_count.insert(map<string, size_t>::value_type(word, 1));
}

void Testing_the_Return_from_insert() { // more verbose way to count number of times each word occurs in the input
	map<string, size_t> word_count; // empty map from string to size_t
	string word;

	while (cin >> word) {
		auto ret = word_count.insert({word, 1}); // inserts an element with key equal to word and value 1; // if word is already in word_count, insert does nothing
		if (!ret.second) //TEST! //																																										word was already in word_count
			++ret.first->second; //TEST! //																																								increment the counter
	}

	for (const auto &i : word_count) //MINE
		cout << i.first << '\t' << i.second << '\n';
	cout << '\n';
}

void Unwinding_the_Syntax() {
	map<string, size_t> word_count;
	string word;

	//TEST! pair<map<string, size_t>::iterator, bool> ret = word_count.insert(make_pair(word, 1));
}

void Adding_Elements_to_multiset_or_multimap() {
	multimap<string, string> authors;

	authors.insert({"Barth, John", "Sot-Weed Factor"}); // adds the first element with the key Barth, John
	authors.insert({"Barth, John", "Lost in the Funhouse"}); // ok: adds the second element with the key Barth, John
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	Testing_the_Return_from_insert();
	//Adding_Elements_to_multiset_or_multimap();

	return 0;
}

#endif

#ifdef EX_11_21

#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	map<string, size_t> word_count;
	string word;

	while (cin >> word)
		//TEST! ++word_count.insert({word, 0}).first->second; 
	
	//TEST! for_each(word_count.cbegin(), word_count.cend(), [](auto &p) { cout << p.first << '\t' << p.second << '\n'; });

	return 0;
}

#endif
