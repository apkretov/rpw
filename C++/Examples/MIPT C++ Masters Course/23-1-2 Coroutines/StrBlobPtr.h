#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

class StrBlob; //MINE Forward declaration.
#include "StrBlob.h" //MINE The ctors below reach into StrBlob, so the class needs to be complete here, not just forward-declared.

class StrBlobPtr { //VER3
	friend void print(StrBlob &); //MINE
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	string &deref() const;
	StrBlobPtr &incr(); // prefix version
	StrBlobPtr &operator++(); // prefix operators
	StrBlobPtr &operator--();
	StrBlobPtr operator++(int); // postfix operators
	StrBlobPtr operator--(int);
	
	string &operator*() const { //TEST
		auto p = check(curr, "dereference past end");
		return (*p)[curr]; // (*p) is the vector to which this object points
	}

	string *operator->() const { return &this->operator*(); } // delegate the real work to the dereference operator
private:
	shared_ptr<vector<string>> check(size_t, const string &) const; // check returns a shared_ptr to the vector if the check succeeds
	weak_ptr<vector<string>> wptr; // store a weak_ptr, which means the underlying vector might be destroyed
	size_t curr; // current position within the array
};

void print(StrBlob &b); //MINE Namespace-scope declaration: the friend declaration inside StrBlobPtr doesn't make the name visible to ordinary lookup in other translation units.
