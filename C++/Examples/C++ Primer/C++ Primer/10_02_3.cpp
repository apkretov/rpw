#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

#ifndef Eliminating_Duplicates
void elimDups(vector<string> &words) {
	sort(words.begin(), words.end()); // sort words alphabetically so we can find the duplicates	
	auto end_unique = unique(words.begin(), words.end()); //TEST! //																																unique reorders the input range so that each word appears once in the front portion of the range and returns an iterator one past the unique range
	words.erase(end_unique, words.end()); // erase uses a vector operation to remove the nonunique elements
}
#endif

void mine(vector<string> v) {
	sort(v.begin(), v.end());
	copy(v.cbegin(), v.cend(), ostream_iterator<string>(cout, " ")); 
	cout << '\n';
}

#ifdef ON
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
	
	//MINE
	auto out = ostream_iterator<string>(cout, " "); 
	copy(words.cbegin(), words.cend(), out); cout << '\n';
	mine(words);

	elimDups(words);
	copy(words.cbegin(), words.cend(), out); cout << '\n'; //MINE

	return 0;
}
#endif

#ifdef EX_10_09
void elimDups() {
	vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
	auto out = ostream_iterator<string>(cout, " "); //MINE

	copy(words.cbegin(), words.cend(), out);
	cout << "\nsize = " << words.size() << "\tcapacity: " << words.capacity() << "\n\n";

	sort(words.begin(), words.end()); // sort words alphabetically so we can find the duplicates	
	cout << "After sort\n";
	copy(words.cbegin(), words.cend(), out);
	cout << "\nsize = " << words.size() << "\tcapacity: " << words.capacity() << "\n\n";

	auto end_unique = unique(words.begin(), words.end());
	cout << "After unique up to end\n";
	copy(words.cbegin(), words.cend(), out);
	cout << "\nup to end_unique\n";
	copy(words.begin(), end_unique, out);
	cout << "\n*end_unique: " << *end_unique;
	cout << "\n*(end_unique + 1): " << *(end_unique + 1);
	cout << "\nsize = " << words.size() << "\tcapacity: " << words.capacity() << "\n\n";

	words.erase(end_unique, words.end()); // erase uses a vector operation to remove the nonunique elements
	cout << "After erase\n";
	copy(words.cbegin(), words.cend(), out);
	cout << "\nsize = " << words.size() << "\tcapacity: " << words.capacity() << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	elimDups();

	return 0;
}
#endif