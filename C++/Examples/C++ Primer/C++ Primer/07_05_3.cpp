#ifdef ON

#include <iostream>
#include "07_05_2.h"
using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << "\n\n";
#ifdef The_Role_of_the_Default_Constructor
	class NoDefault {
	public:
		NoDefault(const std::string &);
		// additional members follow, but no other constructors
	};

	struct A { // my_mem is public by default; see § 7.2 (p. 268)
		NoDefault my_mem;
	};
	//TEST A a; //																																												error: cannot synthesize a constructor for A

	struct B {
		//TEST B() {} //																																										error: no initializer for b_member
		NoDefault b_member;
	};
#elif !Using_the_Default_Constructor
	//TEST Sales_data obj(); //																																									ok: but defines a function, not an object
	//TEST if (obj.isbn() == Primer_5th_ed.isbn()) //																																			error: obj is a function
	Sales_data obj; //																																											ok: obj is a default-initialized object
#endif
	return 0;
}

#endif