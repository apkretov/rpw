#ifdef ON

#include <iostream>
#include "02_06_3.h"
#include <vector>
using namespace std;

int main(int agrc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Sales_data data, *p;
	sizeof(Sales_data); // size required to hold an object of type Sales_data
	sizeof data; // size of data’s type, i.e., sizeof(Sales_data)
	sizeof p; // size of a pointer
	sizeof *p; // size of the type to which p points, i.e., sizeof(Sales_data)
	cout << sizeof data.revenue; //TEST //																																										size of the type of Sales_data’s revenue member
	//TEST! cout << '\n' << sizeof Sales_data::revenue; //																																						alternative way to get the size of revenue

	return 0;
}
#endif

#undef EX_04_29
#ifdef EX_04_29

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int x[10]; 
	int *p = x;

	cout << sizeof(x) / sizeof(*x) << endl;
	cout << sizeof(p) / sizeof(*p) << endl;

	return 0;
}

#endif