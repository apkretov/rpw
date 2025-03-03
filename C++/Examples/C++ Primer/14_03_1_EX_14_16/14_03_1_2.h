#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

#ifndef Defining_the_StrBlob_Class
#ifndef Pointer_Operations
class StrBlobPtr;
#endif

class StrBlob { //VER7 Value-like with equality and inequality operators.
#ifndef Pointer_Operations
	friend class StrBlobPtr;
#endif
#ifndef EX_14_16
	friend bool operator==(const StrBlob &, const StrBlob &);
	friend bool operator!=(const StrBlob &, const StrBlob &);
#endif
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> il);
#ifndef EX_13_25
	StrBlob(const StrBlob &);
	StrBlob &operator=(const StrBlob &);
#endif
	size_type size() const {
		return data->size();
	}

	bool empty() const {
		return data->empty();
	}

	void push_back(const string &t) { // add and remove elements
		cout << "push_back(const string &)\n";
		data->push_back(t);
	}
#ifndef EX_13_55
	void push_back(string &&t) {
		cout << "push_back(string &&)\n";
		data->push_back(std::move(t));
	}
#endif
	void pop_back();
	string &front(); // element access
	string &back();
#ifndef Pointer_Operations
#ifndef EX_12_32
	StrBlobPtr begin(); // return StrBlobPtr to the first element
	StrBlobPtr end(); // and one past the last element
#else
	StrBlobPtr begin() const; // return StrBlobPtr to the first element
	StrBlobPtr end() const; // and one past the last element
#endif
#endif
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
#endif

#ifndef StrBlob_Constructors
StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {
	//cout << "StrBlob constructor\tuse_count: " << data.use_count() << '\n';
}
#endif

#ifndef EX_13_25
StrBlob::StrBlob(const StrBlob &b) : data(make_shared<vector<string>>(*b.data)) {
	//cout << "StrBlob copy constructor\tuse_count: " << data.use_count() << '\n';
}

StrBlob &StrBlob::operator=(const StrBlob &b) {
	data = make_shared<vector<string>>(*b.data);
	//cout << "StrBlob copy-assignment\tuse_count: " << data.use_count() << '\n';
	return *this;
}
#endif

#ifndef Element_Access_Members
void StrBlob::check(size_type i, const string &msg) const {
	if (i > data->size())
		throw out_of_range(msg);
}

string &StrBlob::front() {
	check(0, "front on empty StrBlob"); // if the vector is empty, check will throw
	return data->front();
}

string &StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
#endif

#ifndef EX_14_16
bool operator==(const StrBlob &lhs, const StrBlob &rhs) {
	return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs) {
	return !(lhs == rhs);
}
#endif