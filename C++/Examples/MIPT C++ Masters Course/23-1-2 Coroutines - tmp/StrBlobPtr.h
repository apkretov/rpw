#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "StrBlob.h"

class StrBlob;

class StrBlobPtr { //VER3
	friend std::ostream& operator<<(std::ostream&, const StrBlob&); //MINE
public:
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	StrBlobPtr &operator++(); // prefix operators
	StrBlobPtr &operator--();
	StrBlobPtr operator++(int); // postfix operators
	StrBlobPtr operator--(int);
	std::string& operator*() const;
	std::string *operator->() const { return &this->operator*(); } // delegate the real work to the dereference operator
	bool operator==(const StrBlobPtr&) const;
	bool operator!=(const StrBlobPtr&) const;
private:
	std::shared_ptr<std::vector<std::string>> check(size_t, const std::string &) const; // check returns a shared_ptr to the vector if the check succeeds
	std::weak_ptr<std::vector<std::string>> wptr; // store a weak_ptr, which means the underlying vector might be destroyed
	size_t curr; // current position within the array
};

std::ostream& operator<<(std::ostream&, const StrBlob&); //MINE Namespace-scope declaration: the friend declaration inside StrBlobPtr doesn't make the name visible to ordinary lookup in other translation units.
