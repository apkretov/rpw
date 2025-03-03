#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

class StrBlob; //MINE Forward declaration.

#ifndef Checked_Pointer_Class // StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr { //VER2
	friend void print(StrBlob &); //MINE
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	std::string &deref() const;
	StrBlobPtr &incr(); // prefix version
#ifndef Defining_Prefix_Increment_Decrement_Operators // increment and decrement
	StrBlobPtr &operator++(); // prefix operators
	StrBlobPtr &operator--();
#endif // other members as before
#ifndef Differentiating_Prefix_and_Postfix_Operators // increment and decrement
	StrBlobPtr operator++(int); // postfix operators
	StrBlobPtr operator--(int);
#endif // other members as before
private:
	std::shared_ptr<std::vector<std::string>> check(size_t, const std::string &) const; // check returns a shared_ptr to the vector if the check succeeds
	std::weak_ptr<std::vector<std::string>> wptr; // store a weak_ptr, which means the underlying vector might be destroyed
	size_t curr; // current position within the array
};
#endif

#include "12_01_6_2.h" //MINE This header must be here.
#include "14_06_2.h" //MINE This header must be here.