#ifdef ON

#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

void Accessing_Elements() {
	set<int> iset = {0,1,2,3,4,5,6,7,8,9};
	iset.find(1); // returns an iterator that refers to the element with key == 1
	iset.find(11); // returns the iterator == iset.end()
	iset.count(1); // returns 1
	iset.count(11); // returns 0
}

void Using_find_Instead_of_Subscript_for_maps() {
	map<string, size_t> word_count; //MINE

	if (word_count.find("foobar") == word_count.end())
		cout << "foobar is not in the map" << endl;
}

multimap<string, string> authors = {{"Alain de Botton", "book 1"}, {"Alain de Botton", "book 2"}}; //MINE
string search_item("Alain de Botton"); // author we’ll look for

#ifdef OFF
void Finding_Elements_in_a_multimap_or_multiset() {
	auto entries = authors.count(search_item); // number of elements
	//TEST! auto iter = authors.find(search_item); //																																				first entry for this author
	while (entries) { // loop through the number of entries there are for this author
		cout << iter->second << endl; // print each title
		++iter; // advance to the next title
		--entries; // keep track of how many we’ve printed
	}
}
#endif

#ifdef OFF
void A_Different_Iterator_Oriented_Solution() { // definitions of authors and search_item as above
	//TEST! for (auto beg = authors.lower_bound(search_item), end = authors.upper_bound(search_item); beg != end; ++beg) //																			beg and end denote the range of elements for this author
		cout << beg->second << endl; // print each title
}
#endif

#ifdef OFF
void The_equal_range_Function() { // definitions of authors and search_item as above
	//TEST! for (auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first) //																								pos holds iterators that denote the range of elements for this key
		cout << pos.first->second << endl; // print each title
}
#endif

#ifdef Building_the_Transformation_Map

map<string, string> buildMap(ifstream &map_file) {
	map<string, string> trans_map; // holds the transformations
	string key; // a word to transform
	string value; // phrase to use instead
	
	//TEST! while (map_file >> key && getline(map_file, value)) // read the first word into key and the rest of the line into value
		if (value.size() > 1) // check that there is a transformation
			trans_map[key] = value.substr(1); // skip leading space
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
}
#endif

#ifndef Generating_a_Transformation

const string &transform(const string &s, const map<string, string> &m) {
	auto map_it = m.find(s); // the actual map work; this part is the heart of the program
	
	if (map_it != m.cend()) // if this word is in the transformation map
		return map_it->second; // use the replacement word
	else
		return s; // otherwise return the original unchanged
}
#endif

#ifdef The_Word_Transformation_Program

void word_transform(ifstream &map_file, ifstream &input) {
	auto trans_map = buildMap(map_file); // store the transformations
	string text; // hold each line from the input

	while (getline(input, text)) { // read a line of input
		istringstream stream(text); // read each word
		string word;
		bool firstword = true; // controls whether a space is printed
		
		while (stream >> word) {
			if (firstword)
				firstword = false;
			else
				cout << " "; // print a space between words
			// transform returns its first argument or its transformation
			cout << transform(word, trans_map); // print the output
		}
		cout << endl; // done with this line of input
	}
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	//Finding_Elements_in_a_multimap_or_multiset();
	//A_Different_Iterator_Oriented_Solution();
	//The_equal_range_Function();
	
	ifstream map_file("map_file.txt"), input("input.txt");
	//word_transform(map_file, input);

	return 0;
}

#endif
