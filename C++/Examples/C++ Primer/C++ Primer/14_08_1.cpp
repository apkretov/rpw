#ifdef ON

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void Lambdas_Are_Function_Objects(vector<string> &words) {
	ostream_iterator<string> out(cout, " ");
	copy(words.cbegin(), words.cend(), out); cout << '\n';

	stable_sort(words.begin(), words.end(), [](const string &a, const string &b) { return a.size() < b.size(); }); // sort words by size, but maintain alphabetical order for words of the same size
	copy(words.cbegin(), words.cend(), out); cout << '\n'; //MINE
	
	class ShorterString { //TEST!
	public:
		bool operator()(const string &s1, const string &s2) const {
			return s1.size() < s2.size();
		}
	};

	stable_sort(words.begin(), words.end(), ShorterString()); //TEST!
	copy(words.cbegin(), words.cend(), out); cout << '\n'; //MINE
}

void Classes_Representing_Lambdas_with_Captures(vector<string> &&words) {
	constexpr size_t sz = 3; //MINE
	auto wc = find_if(words.begin(), words.end(), [sz](const string &a) { return a.size() >= sz; }); // get an iterator to the first element whose
	cout << *wc << '\n'; //MINE

	class SizeComp { 
	public:
		SizeComp(size_t n) : sz(n) {} //TEST! //																																											parameter for each captured variable
		bool operator()(const string &s) const { // call operator with the same return type, parameters, and body as the lambda
			return s.size() >= sz;
		}
	private:
		size_t sz; //TEST! //																																																a data member for each variable captured by value
	};

	//MINE
	wc = find_if(words.begin(), words.end(), SizeComp(sz));
	cout << *wc << '\n';
}

int main(int argc, char *argv[]) {
	print_file_line();

	//MINE
	ifstream filein(argv[1]	);
	istream_iterator<string> in(filein), eof;
	vector<string> words(in, eof);
	
	Lambdas_Are_Function_Objects(words);
	Classes_Representing_Lambdas_with_Captures(std::move(words));

	return 0;
}
#endif