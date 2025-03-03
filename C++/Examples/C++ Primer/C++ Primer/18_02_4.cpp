#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Argument-Dependent Lookup and Overloading
namespace NS {
	class Quote { /* ... */ };

	void display(const Quote &) { 
		/* ... */ 
		cout << "void display(const Quote &)" << '\n';
	}
}

class Bulk_item : public NS::Quote { /* ... */ }; // Bulk_item’s base class is declared in namespace NS
#pragma endregion

#ifdef Overloading_and_using_Directives
namespace libs_R_us {
	extern void print(int);
	extern void print(double);
}

void print(const string &); // ordinary declaration

using namespace libs_R_us; // this using directive adds names to the candidate set for calls to print:
// the candidates for calls to print at this point in the program are:
// print(int) from libs_R_us
// print(double) from libs_R_us
// print(const std::string &) declared explicitly

void fooBar(int ival) {
	print("Value: "); // calls global print(const string &)
	print(ival); // calls libs_R_us::print(int)
}
#endif

#define Overloading_across_Multiple_using_Directives
#ifdef Overloading_across_Multiple_using_Directives
namespace AW {
	int print(int i) { //ORIG int print(int);
		cout << "int print(int i): i = " << i << '\n';
		return i;
	}
}

namespace Primer {
	double print(double d) { //ORIG double print(double);
		cout << "double print(double d): d = " << d << '\n';
		return d;
	}
}

using namespace AW; // using directives create an overload set of functions from different namespaces
using namespace Primer;
long double print(long double);
#endif

int main() {
	print_file_line();

#ifdef Argument_Dependent_Lookup_and_Overloading
	Bulk_item book1;
	display(book1);
#endif

#ifdef Overloading_across_Multiple_using_Directives
	print(1); // calls AW::print(int)
	print(3.1); // calls Primer::print(double)
#endif

	return 0;
}
#endif

#ifdef EX_18_20

#include <iostream>
#include "../../stdafx.h"
using namespace std;

namespace primerLib {
	void compute();
	void compute(const void *);
}

#undef _1
#define _2
#ifdef _1
using primerLib::compute;
#endif 

void compute(int i) { //ORIG void compute(int)
	cout << "void compute(int i): i = " << i << '\n';
}

void compute(double, double = 3.4);
void compute(char *, char * = 0);

void f() {
	compute(0);
}

int main() {
	print_file_line();

#ifdef _2
using primerLib::compute;
#endif 
	f();

	return 0;
}
#endif