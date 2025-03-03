#ifdef ON

#include <iostream>
#include <map>
#include <set>
using namespace std;

void Using_a_map() { // count the number of times each word occurs in the input
	map<string, size_t> word_count; // empty map from string to size_t
	string word;
	
	while (cin >> word)
		++word_count[word]; //TEST! //																																								fetch and increment the counter for word
	
	for (const auto &w : word_count) // for each element in the map
		cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl; // print the results
}

void Using_a_set() { // count the number of times each word occurs in the input
	map<string, size_t> word_count; // empty map from string to size_t
	set<string> exclude = {"The", "But", "And", "Or", "An", "A", "the", "but", "and", "or", "an", "a"};
	string word;
	
	while (cin >> word)
		if (exclude.find(word) == exclude.end()) //TEST! //																																			count only words that are not in exclude
			++word_count[word]; // fetch and increment the counter for word
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	//Using_a_map();
	Using_a_set();

	return 0;
}

#endif
