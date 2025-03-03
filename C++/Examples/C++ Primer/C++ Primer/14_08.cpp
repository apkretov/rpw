#ifdef ON

#include <iostream>
#include <algorithm>
#include <vector>
#include "../../stdafx.h"
using namespace std;

void Function_Call_Operator() {
	struct absInt {
		int operator()(int val) const { //TEST!!
			return val < 0 ? -val : val;
		}
	};

	int i = -42;
	absInt absObj; // object that has a function-call operator
	int ui = absObj(i); // passes i to absObj.operator()

	cout << ui << '\n';	//MINE
}

void mine() {
	struct {
		int operator()(int n) {
			return ++n;
		}
	} incr;

	vector<int> v(10);
	fill_n(v.begin(), v.size(), 111); 
	ostream_iterator<int> out(cout, " ");
	copy(v.cbegin(), v.cend(), out); cout << '\n';

	transform(v.begin(), v.end(), v.begin(), incr); //TEST!
	copy(v.cbegin(), v.cend(), out); cout << '\n';
}

void Function_Object_Classes_with_State() {
	class PrintString {
	public:
		PrintString(ostream &o = cout, char c = ' ') : os(o), sep(c) {}
		void operator()(const string &s) const { os << s << sep; } //TEST!
	private:
		ostream &os; // stream on which to write
		char sep; // character to print after each output
	};

	string s = "abc"; //MINE
	PrintString printer; // uses the defaults; prints to cout
	printer(s); // prints s followed by a space on cout
	PrintString errors(cerr, '\n');
	errors(s); // prints s followed by a newline on cerr

	//MINE
	cout << "\nFill in the string vector:\n";
	istream_iterator<string> in(cin), eof;
	vector<string> vs(in, eof);

	for_each(vs.begin(), vs.end(), PrintString(cerr, '\n'));
	cout << '\n'; //MINE
}

int main(int argc, char *argv[]) {
	print_file_line();

	//Function_Call_Operator();
	mine();
	//Function_Object_Classes_with_State();

	return 0;
}
#endif
