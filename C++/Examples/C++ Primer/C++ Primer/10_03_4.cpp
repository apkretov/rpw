#ifdef ON

#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
using namespace std;

# ifndef Using_placeholders_Names
using namespace std::placeholders; //TEST!!
#endif

vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"}; //MINE

#ifndef Binding_Arguments
bool check_size(const string &s, string::size_type sz) {
	return s.size() >= sz;
}
#endif

void Binding_the_sz_Parameter_of_check_size() {
	auto check6 = bind(check_size, _1, 6); //TEST!! //																																		check6 is a callable object that takes one argument of type string and calls check_size on its given string and the value 6

	string s = "hello";
	bool b1 = check6(s); //TEST! //																																							check6(s) calls check_size(s, 6)

	vector<string>::size_type sz{6}; //MINE
	auto wc = find_if(words.cbegin(), words.cend(), [sz](const string &s) {return s.size() >= sz; });
	wc = find_if(words.begin(), words.end(), bind(check_size, _1, sz)); //TEST!
	
	//MINE
	wc = find_if(words.begin(), words.end(), check6); //TEST!
	cout << "*wc = " << *wc << '\n';

	//MINE
	//TEST! auto check_mine = bind(check_size, _2, _1);
	//TEST! bool b2 = check_mine(6, s);
}

void Using_to_bind_to_Reorder_Parameters() {
	//MINE
	bool isShorter(const string & s1, const string & s2); 
	auto out = ostream_iterator<string>(cout, " ");
	copy(words.cbegin(), words.cend(), out); cout << '\n';

	sort(words.begin(), words.end(), isShorter); // sort on word length, shortest to longest
	copy(words.cbegin(), words.cend(), out); cout << '\n'; //MINE
	
	sort(words.begin(), words.end(), bind(isShorter, _2, _1)); // sort on word length, longest to shortest
	copy(words.cbegin(), words.cend(), out); cout << '\n'; //MINE
}

#ifndef Binding_Reference_Parameters
void print(ostream &os, const string &s, char c) {
	os << s << c;
}

void Binding_Reference_Parameters(ostream &os) {
	// os is a local variable referring to an output stream
	// c is a local variable of type char
	char c{' '}; //MINE
	for_each(words.begin(), words.end(), [&os, c](const string &s) { os << s << c; });
	cout << '\n'; //MINE

	//TEST!! for_each(words.begin(), words.end(), bind(print, os, _1, ' ')); //																														error: cannot copy os
	for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' ')); //TEST!!
	cout << '\n'; //MINE
}
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Binding_the_sz_Parameter_of_check_size();
	//Using_to_bind_to_Reorder_Parameters();
	//Binding_Reference_Parameters(cout);

	return 0;
}
#endif

#ifdef EX_10_22

#include <iostream>
#include <algorithm>
#include <functional>
#include <fstream>
#include <vector>
using namespace std;
using namespace std::placeholders;

bool check_size(const string &s, string::size_type sz) {
	return s.size() <= sz;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	fstream in(argv[1]);
	istream_iterator<string> it(in), eof;
	vector<string> v(it, eof);
	
	copy(v.cbegin(), v.cend(), ostream_iterator<string>(cout, " "));
	cout << '\n';

	auto cnt = count_if(v.cbegin(), v.cend(), bind(check_size, _1, 6));
	cout << cnt << '\n';

	return 0;
}
#endif