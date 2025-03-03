#pragma once

#include <string>
#include <vector>
#include <memory>
using namespace std;

#ifndef Defining_the_StrBlob_Class
class StrBlob { //VER1 Pointer-like.
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

	void push_back(const string &t) { // add and remove elements
		data->push_back(t);
	}

	void pop_back();
	string &front(); // element access
	string &back();
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
#endif

#include "12_01_1_2.h" //MINE This header must be here.

#ifndef Element_Access_Members
string &StrBlob::front() {
	check(0, "front on empty StrBlob"); // if the vector is empty, check will throw
	return data->front();
}

string &StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}
#endif
