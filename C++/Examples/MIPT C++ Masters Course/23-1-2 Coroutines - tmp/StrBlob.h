#pragma once

#include <vector>
#include <string>
#include <memory>

class StrBlobPtr;

class StrBlob { //VER7 Value-like with equality and inequality operators.
	friend class StrBlobPtr;
	friend bool operator==(const StrBlob &, const StrBlob &);
	friend bool operator!=(const StrBlob &, const StrBlob &);
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	StrBlob(const StrBlob &);
	StrBlob &operator=(const StrBlob &);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t); // add and remove elements
	void push_back(std::string&& t);
	void pop_back();
	std::string &front(); // element access
	std::string &back();
	StrBlobPtr begin() const; //TEST // these members can’t be defined until StrStrBlob and StrStrBlobPtr are defined
	StrBlobPtr end() const; 
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const; // throws msg if data[i] isn't valid
};

#include "StrBlobPtr.h" //TEST // begin() and end() members can’t be defined until StrStrBlob and StrStrBlobPtr are defined
