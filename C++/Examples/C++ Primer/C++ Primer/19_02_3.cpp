#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region The Class Hierarchy
class Base {
	friend bool operator==(const Base &, const Base &);
public:
	// interface members for Base
protected:
	virtual bool equal(const Base &) const;
	// data and other implementation members of Base
};

class Derived : public Base {
public:
	// other interface members for Derived
protected:
	bool equal(const Base &) const;
	// data and other implementation members of Derived
};
#pragma endregion

#pragma region A Type-Sensitive Equality Operator
bool operator==(const Base &lhs, const Base &rhs) {
	// returns false if typeids are different; otherwise makes a virtual call to equal
	return typeid(lhs) == typeid(rhs) && lhs.equal(rhs); //TEST
}
#pragma endregion

#pragma region The Virtual equal Functions
bool Derived::equal(const Base &rhs) const {
	auto r = dynamic_cast<const Derived &>(rhs); //TEST //																								we know the types are equal, so the cast won’t throw
	// do the work to compare two Derived objects and return the result
	return true; //MINE
}
#pragma endregion

#pragma region The Base-Class equal Function
bool Base::equal(const Base &rhs) const {
	// do whatever is required to compare to Base objects
	return true; //MINE
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif