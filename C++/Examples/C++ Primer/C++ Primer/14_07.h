#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

class StrBlob; //MINE Forward declaration.

#ifndef Checked_Pointer_Class // StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr { //VER3
	friend void print(StrBlob &); //MINE
public:
	StrBlobPtr() : curr(0) {}
#ifndef EX_12_32
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
#else
	StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
#endif
	string &deref() const;
	StrBlobPtr &incr(); // prefix version
#ifndef Defining_Prefix_Increment_Decrement_Operators // increment and decrement
	StrBlobPtr &operator++(); // prefix operators
	StrBlobPtr &operator--();
#endif // other members as before
#ifndef Differentiating_Prefix_and_Postfix_Operators // increment and decrement
	StrBlobPtr operator++(int); // postfix operators
	StrBlobPtr operator--(int);
#endif // other members as before
#ifndef Member_Access_Operators
	string &operator*() const { //TEST
		auto p = check(curr, "dereference past end");
		return (*p)[curr]; // (*p) is the vector to which this object points
	}

	string *operator->() const { // delegate the real work to the dereference operator
		return &this->operator*();
	}
#endif // other members as before
private:
	shared_ptr<vector<string>> check(size_t, const string &) const; // check returns a shared_ptr to the vector if the check succeeds
	weak_ptr<vector<string>> wptr; // store a weak_ptr, which means the underlying vector might be destroyed
	size_t curr; // current position within the array
};
#endif

#include "12_01_6_2.h" //MINE This header must be here.
#include "14_06_2.h" //MINE This header must be here.