#undef ON
#ifdef ON

#include <iostream>
using std::cout;

double pi = 3.1416;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	extern double pi /*ORIG = 3.1415*/;
	cout << pi << '\n';
}
#endif
