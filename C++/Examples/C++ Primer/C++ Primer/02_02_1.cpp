#undef ON
#ifdef ON

#include <iostream>
using std::cout;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	long double ld = 3.1415926536;
	//ORIG int a{ld}, b = {ld};
	int c(ld), d = ld;

	cout << c << '\t' << d << '\n';
}
#endif

#undef EX_02_09
#ifdef EX_02_09

#include <iostream>
using std::cout;
using std::cin;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//ORIG cin >> int input_value;
	//ORIG int i = {3.14};
	//ORIG double sarary = wage = 9999.99;
	int i = 3.14;

	cout << i << '\n';
}
#endif