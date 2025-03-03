#ifdef ON

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef Capture_by_Value {
void fcn1() {
	size_t v1 = 42; // local variable
	auto f = [v1] { return v1; }; // copies v1 into the callable object named f
	v1 = 0;
	auto j = f(); //TEST! //																																								j is 42; f stored a copy of v1 when we created it
	cout << j << '\n'; //MINE
}
#endif

namespace Capture_by_Reference {
	void fcn2() {
		size_t v1 = 42; // local variable
		auto f2 = [&v1] { return v1; }; // the object f2 contains a reference to v1
		v1 = 0;
		auto j = f2(); //TEST! //																																								j is 0; f2 refers to v1; it doesn’t store it
		cout << j << '\n'; //MINE
	}

	void biggies(vector<string> &words, vector<string>::size_type sz, ostream &os = cout, char c = ' ') {
		for_each(words.begin(), words.end(), [&os, c](const string &s) { os << s << c; }); //TEST! //																							code to reorder words as before // statement to print count revised to print to os
	}
}

namespace Implicit_Captures {
	void f(const vector<string> &words, size_t sz) {
		auto wc = find_if(words.begin(), words.end(), [=](const string &s) { return s.size() >= sz; }); //TEST!  //																				sz implicitly captured by value
	}

	void biggies(vector<string> &words,	vector<string>::size_type sz, ostream &os = cout, char c = ' ') {
		// other processing as before
		for_each(words.begin(), words.end(), [&, c](const string &s) { os << s << c; }); //TEST! //																								os implicitly captured by reference; c explicitly captured by value
		for_each(words.begin(), words.end(), [=, &os](const string &s) { os << s << c; }); //TEST! //																							os explicitly captured by reference; c implicitly captured by value
	}
}

#ifndef Mutable_Lambdas
void fcn3() {
	size_t v1 = 42; // local variable
	auto f = [v1]() mutable { return ++v1; }; //TEST!!! //																																		f can change the value of the variables it captures
	v1 = 0;
	auto j = f(); //TEST!! //																																									j is 43
	cout << v1 << '\t' << j << '\n'; //MINE
}

void fcn4() {
	size_t v1 = 42; // local variable
	auto f2 = [&v1] { return ++v1; }; // v1 is a reference to a nonconst variable	// we can change that variable through the reference inside f2
	v1 = 0;
	auto j = f2(); // j is 1
	cout << j << '\n'; //MINE
}
#endif

void Specifying_the_Lambda_Return_Type(vector<int> &vi) {
	transform(vi.begin(), vi.end(), vi.begin(),	[](int i) { return i < 0 ? -i : i; }); //TEST!!
	
	transform(vi.begin(), vi.end(), vi.begin(),	[](int i) { if (i < 0) return -i; else return i; }); //TEST!!																					//MINE: OK // error: cannot deduce the return type for the lambda

	transform(vi.begin(), vi.end(), vi.begin(), [](int i) -> int { if (i < 0) return -i; else return i; }); //TEST!
}

void mine1() {
	vector<int> v = {-2, -1, 0, 1, 2};
	Specifying_the_Lambda_Return_Type(v);
	for_each(v.cbegin(), v.cend(), [](int i) { cout << i << ' '; });
	cout << '\n';
}

void mine2() {
	auto f = [](int i) { if (i < 0)
		return -i;
	else
		return i;
	};
	
	auto n = f(-1);
	cout << n << '\n';
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//fcn1();
	//Capture_by_Reference::fcn2();
	fcn3();
	//fcn4();
	//mine1();
	//mine2();

	return 0;
}
#endif

#ifdef EX_10_20

#include <iostream>
#include <algorithm>
#include <fstream>
#include<vector>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	ifstream in(argv[1]);
	istream_iterator<string> is(in), eof;
	vector<string> v(is, eof);
	
	ostream_iterator<string> out(cout, " ");
	copy(v.cbegin(), v.cend(), out); cout << '\n';

	auto len = [](const string &s) { return s.length() > 2; };
	auto n = count_if(v.cbegin(), v.cend(), len);
	cout << "count_if length > 2: " << n << "\n\n";

	sort(v.begin(), v.end());
	copy(v.cbegin(), v.cend(), out); cout << '\n';

	n = count_if(v.cbegin(), v.cend(), len);
	cout << "count_if length > 2: " << n << '\n';

	return 0;
}
#endif