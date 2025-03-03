#ifdef ON

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isShorter(const string &s1, const string &s2); //MINE

void Predicates() {
	vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"}; //MINE
	
	copy(words.cbegin(), words.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';
	//TEST! sort(words.begin(), words.end(), isShorter); //																																			sort on word length, shortest to longest
	copy(words.cbegin(), words.cend(), ostream_iterator<string>(cout, " ")); cout << '\n';

}
  
void Sorting_Algorithms() {
	//MINE
	vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
	void elimDups(vector<string> &words);
	
	elimDups(words); // put words in alphabetical order and remove duplicates
	stable_sort(words.begin(), words.end(), isShorter); //TEST! //																																	resort by length, maintaining alphabetical order among words of the same length
	for (const auto &s : words) // no need to copy the strings
		cout << s << " "; // print each element separated by a space
	cout << endl;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//Predicates();
	Sorting_Algorithms();

	return 0;
}
#endif

#ifdef EX_10_12

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "07_05_4.h"

#ifdef OFF
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
	return lhs.isbn() < rhs.isbn();
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//OFF istream_iterator<Sales_data> in(cin), eof;
#ifdef INPUT_1
	vector<Sales_data> v(in, eof); // Input one.
#elif INPUT_2
	vector<Sales_data> v;
	while (in != eof)
		v.push_back(*in++);
		
#elif! INTPUT_3
	vector<Sales_data> v;
	auto it = back_inserter(v);
	while (in != eof)
		it = *in++;
#elif! _
	vector<Sales_data> v;
	Sales_data sd;
	while (read(cin, sd)) {
		v.push_back(sd);
	}

#endif
	bool compareIsbn(const Sales_data & lhs, const Sales_data & rhs);
	sort(v.begin(), v.end(), compareIsbn);
	for (const auto &it : v) {
		print(cout, it);
		cout << '\n';
	}

	return 0;
}
#endif