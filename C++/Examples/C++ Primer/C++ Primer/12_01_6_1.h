#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
using std::shared_ptr;
using std::weak_ptr;
using std::vector;
using std::string;
using std::cout;

class StrBlob; //MINE Forward declaration.

#ifndef Checked_Pointer_Class // StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr { //VER1
	friend void print(StrBlob &); //MINE
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {} //TEST!! //																				we cannot bind a StrBlobPtr to a const StrBlob object - the constructor takes a reference to nonconst StrBlob.
	string &deref() const;
	StrBlobPtr &incr(); // prefix version
private:
	shared_ptr<vector<string>> check(size_t, const string &) const; // check returns a shared_ptr to the vector if the check succeeds
	weak_ptr<vector<string>> wptr; // store a weak_ptr, which means the underlying vector might be destroyed
	size_t curr; // current position within the array
};
#endif

#include "12_01_6_2.h" //MINE This header must be here.

void print(StrBlob &b) { //MINE
	auto it = b.begin();
	for (StrBlob::size_type i{}; i < b.size(); ++i) {
		cout << it.deref() << ' ';
		it.incr();
	}
	cout << '\n';
}
