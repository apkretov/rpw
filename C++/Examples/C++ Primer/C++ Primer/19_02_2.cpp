#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region MINE
struct Base {
	virtual ~Base() = default;
};

struct Derived : Base {};

struct NonVirtualBase {};
struct NonVirtualDerived : NonVirtualBase {};
#pragma endregion
	
void Using_the_typeid_Operator() {
	Derived *dp = new Derived;
	Base *bp = dp; // both pointers point to a Derived object
	
	if (typeid(*bp) == typeid(*dp)) { //TEST! //																										compare the type of two objects at run time
		// bp and dp point to objects of the same type
		cout << "bp and dp point to objects of the same type\n"; //MINE
	}
	
	if (typeid(*bp) == typeid(Derived)) { // test whether the run-time type is a specific type
		// bp actually points to a Derived
		cout << "bp actually points to a Derived\n"; //MINE	
	}

#pragma region MINE
	NonVirtualDerived *ndp = new NonVirtualDerived;
	NonVirtualBase *nbp = ndp;

	if (typeid(*nbp) == typeid(*ndp)) //TEST!
		cout << "\nnbp and ndp point to objects of the same type\n";
	else
		cout << "\nbp and ndp point to objects of different types\n";
#pragma endregion

	if (typeid(bp) == typeid(Derived)) { //TEST! //																										test always fails: the type of bp is pointer to Base
		// code never executed
		cout << "code never executed\n"; //MINE
	}
}

int main() {
	print_file_line();

	Using_the_typeid_Operator();

	return 0;
}
#endif
