#ifdef ON

#include <iostream>
#include <map>
using namespace std;

void Erasing_Elements() {
	map<string, size_t> word_count = {{"a", 0}, {"b", 1}, {"c", 2}}; //MINE
	string removal_word = word_count.cbegin()->first; //TEST! //MINE
	if (word_count.erase(removal_word)) // erase on a key returns the number of elements removed
		cout << "ok: " << removal_word << " removed\n";
	else 
		cout << "oops: " << removal_word << " not found!\n";

	multimap<string, string> authors = {{"Barth, John", "book 1"}, {"Barth, John", "book 2"}, {"Smith, John", "book 1"}}; //MINE
	auto cnt = authors.erase("Barth, John");
	cout << cnt << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	Erasing_Elements();

	return 0;
}

#endif
