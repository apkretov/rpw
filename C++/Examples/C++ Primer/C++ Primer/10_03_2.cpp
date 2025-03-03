#ifdef ON

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#include "06_03_2.h"

#ifndef Lambda_Expressions
void biggies(vector<string> &words,	vector<string>::size_type sz) {
	//MINE
	void elimDups(vector<string> &words);
	bool isShorter(const string & s1, const string & s2);

	elimDups(words); // put words in alphabetical order and remove duplicates
	// resort by length, maintaining alphabetical order among words of the same length
	stable_sort(words.begin(), words.end(), isShorter);
	// get an iterator to the first element whose size() is >= sz
	// compute the number of elements with size >= sz
	// print words of the given size or longer, each one followed by a space

#ifndef Using_the_Capture_List
	[sz](const string &a) { return a.size() >= sz; };
	//TEST! [](const string &a) { return a.size() >= sz; }; //																																		error: sz not captured
#endif

#ifndef Calling_find_if
	auto wc = find_if(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; }); //TEST! //																						get an iterator to the first element whose size() is >= sz

	// compute the number of elements with size >= sz
	auto count = words.end() - wc;
	cout << count << " " << How_Values_Are_Returned::make_plural(count, "word", "s")	<< " of length " << sz << " or longer" << endl;
#endif

#ifndef The_for_each_Algorithm
	for_each(wc, words.end(), [](const string &s) {cout << s << " "; }); //TEST! // print words of the given size or longer, each one followed by a space
	cout << endl;
#endif

#ifdef Putting_It_All_Together
	elimDups(words); // put words in alphabetical order and remove duplicates
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) { return a.size() < b.size(); }); // sort words by size, but maintain alphabetical order for words of the same size
	auto wc = find_if(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; }); // get an iterator to the first element whose size() is >= sz
	auto count = words.end() - wc; // compute the number of elements with size >= sz
	cout << count << " " << How_Values_Are_Returned::make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;
	for_each(wc, words.end(), [](const string &s) {cout << s << " "; }); // print words of the given size or longer, each one followed by a space
	cout << endl;
#endif
}
#endif

void Introducing_Lambdas() {
	// [capture list] (parameter list) -> return type{function body}

	//TEST! auto f = [] { return 42; };
#ifdef OFF
	cout << f() << endl; //																																									prints 42
#endif
}

void mine(vector<string> &words) {
	void elimDups(vector<string> &words);

	elimDups(words); // put words in alphabetical order and remove duplicates
	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {return a.size() < b.size(); });
	for (const auto &i : words)
		cout << i << ' ';
	cout << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"}; //MINE
	biggies(words, 5);

	//Introducing_Lambdas();

	//mine(words);

	return 0;
}
#endif