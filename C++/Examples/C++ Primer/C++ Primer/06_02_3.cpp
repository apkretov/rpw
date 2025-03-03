#ifdef ON

#include <iostream>
using namespace std;

void Use_Reference_to_const_When_Possible() {
	string::size_type ctr{}; //MINE

	//TEST string::size_type find_char(string & s, char c, string::size_type & occurs); //																									bad design: the first parameter should be a const string&
	//TEST find_char("Hello World", 'o', ctr);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	return 0;
}

string::size_type find_char(/*ORIG const*/ string &s, char c, string::size_type &occurs) { // returns the index of the first occurrence of c in s the reference parameter occurs counts how often c occurs
	auto ret = s.size(); // position of the first occurrence, if any
	occurs = 0; // set the occurrence count parameter
	for (decltype(ret) i = 0; i != s.size(); ++i) {
		if (s[i] == c) {
			if (ret == s.size())
				ret = i; // remember the first occurrence of c
			++occurs; // increment the occurrence count
		}
	}
	return ret; // count is returned implicitly in occurs
}
#endif