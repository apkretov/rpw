#ifdef ON

#include <iostream>
#include <bitset>
#include <climits>
#include "../../stdafx.h"
using namespace std;

void Using_Bitwise_Operators() {
	unsigned long quiz1 = 0; // we’ll use this value as a collection of bits
	
	using bs = bitset<CHAR_BIT * sizeof quiz1>;
	quiz1 |= 1UL << 27; //TEST! //																																									indicate student number 27 passed
	cout << bs(quiz1) << '\n';

	quiz1 &= ~(1UL << 27); //TEST //																																								student number 27 failed
	cout << bs(quiz1) << '\n';

#ifdef ON
	//TEST bool status = quiz1 & (1UL << 27); //																																					how did student number 27 do?
	cout << status << '\n';
#endif
}

int main() {
	print_file_line();

	Using_Bitwise_Operators();
}
#endif

#ifdef EX_04_25

#include <iostream>
#include <bitset>
#include <climits>
using namespace std;

int main(int agrc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	using bs = bitset<CHAR_BIT * sizeof(int)>;
	cout << bs('q') << '\n';
	cout << bs('q' << 6) << '\n';
	cout << bs(~('q' << 6)) << '\n'; //TEST

	return 0;
}
#endif

#ifdef EX_04_27

#include <iostream>
#include <climits>
#include <bitset>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	unsigned long ul1 = 3, ul2 = 7;
	using bs = bitset<CHAR_BIT * sizeof ul1>;

	cout << bs(ul1) << '\n' << bs(ul2) << '\n';

	cout << bs(ul1 & ul2) << '\n'; // (a) //TEST
	cout << bs(ul1 | ul2) << '\n'; // (b) //TEST 
	cout << boolalpha << (ul1 && ul2) << '\n'; // (c) //TEST
	cout << boolalpha << (ul1 || ul2) << '\n'; // (d) //TEST

	return 0;
}
#endif