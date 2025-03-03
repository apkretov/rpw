#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifndef Defining_a_Derived_Copy_or_Move_Constructor
class Base { /* ... */
public:
	Base &operator=(const Base &) { //MINE
		return *this; 
	} 
};

class D : public Base {
public: // by default, the base class default constructor initializes the base part of an object // to use the copy or move constructor, we must explicitly call that // constructor in the constructor initializer list
	D(const D &d) : Base(d) //TEST! //																																									copy the base members
		/* initializers for members of D */ {/* ... */
	}

	D(D &&d) : Base(std::move(d)) //TEST! //																																							move the base members
		/* initializers for members of D */ {/* ... */
	}

#ifndef	Derived_Class_Assignment_Operator
	D &operator=(const D &); //MINE
#endif
#ifndef Derived_Class_Destructor // Base::~Base invoked automatically
	~D() { /* do what it takes to clean up derived members */ }
#endif
};
#endif

void Derived_Class_Assignment_Operator_() {
	class D : public Base { //MINE
		//																																																probably incorrect definition of the D copy constructor // base-class part is default initialized, not copied
		D(const D &d) //TEST! /*																																										member initializers, but no base-class initializer */
		{ /* ... */
		}
	};
}

#ifndef	Derived_Class_Assignment_Operator
D &D::operator=(const D &rhs) { // Base::operator=(const Base&) is not invoked automatically
	Base::operator=(rhs); //TEST! //																																									assigns the base part
	// assign the members in the derived class, as usual, // handling self-assignment and freeing existing resources as appropriate
	return *this;
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_15_26

#include <algorithm>
#include "../../stdafx.h"
#include "15_07_3.h"
#include "15_07_3_4.h"
using namespace std;

int main(int argc, char *argv[]) {
	print_file_line();

	objects();
	//pointers_object();
	//pointers_new();

	return 0;
}
#endif