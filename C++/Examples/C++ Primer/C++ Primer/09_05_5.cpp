#ifdef ON

#include <iostream>
#include <string>
using namespace std;

void Numeric_Conversions() {
	int i = 42;
	string s = to_string(i); // converts the int i to its character representation
	double d = stod(s); // converts the string s to floating-point

	string s2 = "pi = 3.14";
	d = stod(s2.substr(s2.find_first_of("+-.0123456789"))); // convert the first substring in s that starts with a digit, d = 3.14
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Numeric_Conversions();

	return 0;
}
#endif
