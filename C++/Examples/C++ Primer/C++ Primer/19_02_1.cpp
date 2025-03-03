#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region MINE
	struct Base {
		virtual ~Base() = default;
	};

	struct Derived : Base {};
#pragma endregion

void Pointer_Type_dynamic_casts() {
	Base *bp = new Derived; //MINE
	if (Derived *dp = dynamic_cast<Derived *>(bp)) { //TEST
		// use the Derived object to which dp points
	} else { // bp points at a Base object
		// use the Base object to which bp points
	}
}

#pragma region Reference-Type dynamic_casts
void f(const Base &b) {
	try { //TEST!
		const Derived &d = dynamic_cast<const Derived &>(b);
		// use the Derived object to which b referred
	}
	catch (bad_cast) {
		// handle the fact that the cast failed
	}
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif
