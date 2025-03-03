#ifdef  ON

#include <iostream>
using namespace std;
#include "06_03_2.h"
using How_Values_Are_Returned::shorterString;

string &shorterString(string &s1, string &s2) {
	auto &r = shorterString(const_cast<const string &>(s1), const_cast<const string &>(s2));
	return const_cast<string &>(r);
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string s1{"short"}, s2{"longer"};
	cout << shorterString(s1, s2) << '\n';

	return 0;
}
#endif

#ifdef EX_06_39

#include <iostream>
using namespace std;

int calc(int, int); // (a)
int calc(const int, const int);

int get(); // (b) 
//TEST double get();

int *reset(int *); // (c)
double *reset(double *);

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine:" << __LINE__ << "\n\n";

	return 0;
}
#endif