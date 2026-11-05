#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
using namespace std;

class StrBlobPtr;

class StrBlob { //VER7 Value-like with equality and inequality operators.
	friend class StrBlobPtr;
	friend bool operator==(const StrBlob &, const StrBlob &);
	friend bool operator!=(const StrBlob &, const StrBlob &);
public:
	typedef vector<string>::size_type size_type;
	StrBlob();
	StrBlob(initializer_list<string> il);
	StrBlob(const StrBlob &);
	StrBlob &operator=(const StrBlob &);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const string &t) { // add and remove elements
		cout << "push_back(const string &)\n";
		data->push_back(t);
	}

	void push_back(string &&t) {
		cout << "push_back(string &&)\n";
		data->push_back(std::move(t));
	}

	void pop_back();
	string &front(); // element access
	string &back();
	StrBlobPtr begin(); // return StrBlobPtr to the first element
	StrBlobPtr end(); // and one past the last element
	StrBlobPtr begin() const; // return StrBlobPtr to the first element
	StrBlobPtr end() const; // and one past the last element
private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
