#pragma once

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>
using namespace std;

#ifndef Defining_the_StrBlob_Class
class StrBlob { //VER3 Pointer-like with more const added.
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

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
#endif

#include "12_01_1_4.h" //MINE This header must be here.