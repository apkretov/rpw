#ifdef ON

#include <string>
using namespace std;
#include "07_05_4.h"

void The_Copy_Assignment_Operator() {
	Sales_data trans, accum;
	trans = accum; // uses the Sales_data copy-assignment operator
}

void Introducing_Overloaded_Assignment() {
	class Foo {
	public:
		Foo &operator=(const Foo &); // assignment operator
		// ...
	};
}

#ifdef The_Synthesized_Copy_Assignment_Operator
	Sales_data & Sales_data::operator=(const Sales_data &rhs) { // equivalent to the synthesized copy-assignment operator
		bookNo = rhs.bookNo; // calls the string::operator=
		units_sold = rhs.units_sold; // uses the built-in int assignment
		revenue = rhs.revenue; // uses the built-in double assignment
		return *this; // return a reference to this object
	}
#endif
#endif