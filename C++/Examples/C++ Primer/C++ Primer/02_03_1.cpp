#undef EX_02_16
#ifdef EX_02_16

#include <iostream>
using std::cout;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	int i = 0, &r1 = i; 
	double d = 0, &r2 = d;

	r2 = r1; // b
	cout << r2 << '\n';

	i = r2; // c
	cout << i << '\n';

	r1 = d; // d
	cout << i << '\n';

	return 0;
}
#endif

#undef EX_02_17
#ifdef EX_02_17

#include <iostream>
using std::cout;

int main(int argc, char** argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i, & ri = i;

	i = 5; 
	ri = 10;
	std::cout << i << " " << ri << std::endl;

	return 0;
}
#endif