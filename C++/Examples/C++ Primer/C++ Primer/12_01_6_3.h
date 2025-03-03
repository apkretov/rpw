#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
using namespace std;

#ifndef Pointer_Operations
	class StrBlobPtr;
#endif

#ifndef Defining_the_StrBlob_Class
class StrBlob { //VER4 Pointer-like with StrBlobPtr.
#ifndef Pointer_Operations
	friend class StrBlobPtr;
#endif
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> il);

	size_type size() const {
		return data->size();
	}

	bool empty() const {
		return data->empty();
	}

	void push_back(const string &t) const { // add and remove elements
		data->push_back(t);
	}

	void pop_back() const;
	string &front() const; // element access
	string &back() const;

#ifndef Pointer_Operations
	StrBlobPtr begin(); // return StrBlobPtr to the first element
	StrBlobPtr end(); // and one past the last element
#endif
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
#endif

#include "12_01_1_4.h" //MINE This header must be here.