#pragma once

#include <string>
using namespace std;

#ifndef Defining_a_Reference_Counted_Class
class HasPtr {
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {} //TEST!! //																								constructor allocates a new string and a new counter, which it sets to 1

	HasPtr(const HasPtr &p) : ps(p.ps), i(p.i), use(p.use) { //TEST!!! //																														copy constructor copies all three data members and increments the counter
		++*use;
	}

	HasPtr &operator=(const HasPtr &);
	~HasPtr();
//ORIG private:
	string *ps;
	int i;
	size_t *use; // member to keep track of how many objects share *ps
};

HasPtr::~HasPtr() {
	if (--*use == 0) { //TEST!! //																																								if the reference count goes to 0
		delete ps; //																																											delete the string
		delete use; // 																																											and the counter
	}
}

HasPtr &HasPtr::operator=(const HasPtr &rhs) {
	++*rhs.use; //TEST!! //																																										increment the use count of the right-hand operand
	if (--*use == 0) { //TEST!! //																																								then decrement this object’s counter
		delete ps; // if no other users
		delete use; // free this object’s allocated members
	}
	ps = rhs.ps; // copy data from rhs into this object
	i = rhs.i;
	use = rhs.use;
	return *this; // return this object
}
#endif