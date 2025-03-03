#ifdef ON

#include <iostream>
#include <ostream>
using namespace std;

#ifndef Classes_That_Act_Like_Values
class HasPtr {
	friend ostream &operator<<(ostream &out, const HasPtr &ph); //MINE
public:
	HasPtr(const string &s = string()) : ps(new string(s)), i(0) {}
	HasPtr(const HasPtr &p) : ps(new string(*p.ps)), i(p.i) {} //TEST! //																															each HasPtr has its own copy of the string to which ps points
	HasPtr &operator=(const HasPtr &);

	~HasPtr() {
		delete ps;
	}
	//ORIG private:
	string *ps;
	int i;
};

inline ostream &operator<<(ostream &out, const HasPtr &hp) { //MINE
	out << *hp.ps;
	//OFF out << '\t' << hp.i;
	return out;
}
#endif

#ifndef Classes_That_Act_Like_Values
HasPtr &HasPtr::operator=(const HasPtr &rhs) { //TEST!
	auto newp = new string(*rhs.ps); // copy the underlying string
	delete ps; // free the old memory
	ps = newp; // copy data from rhs into this object
	i = rhs.i;
	return *this; // return this object
}

#ifdef OFF
HasPtr &HasPtr::operator=(const HasPtr &rhs) { //																																					WRONG way to write an assignment operator!
	delete ps; // frees the string to which this object points
	//TEST! //																																														if rhs and *this are the same object, we’re copying from deleted memory!
	ps = new string(*(rhs.ps));
	i = rhs.i;
	return *this;
}
#endif
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	HasPtr hp1("aaa"), hp2(hp1);
	cout << "hp1 = " << hp1 << '\t' << "hp2 = " << hp2 << '\n';

	hp1.ps = new string("Aaa");
	cout << "hp1 = " << hp1 << '\t' << "hp2 = " << hp2 << '\n';

	return 0;
}
#endif

#ifdef EX_13_25

#include <iostream>
#include <vector>
using namespace std;

#ifndef Defining_the_StrBlob_Class
#ifndef Pointer_Operations
class StrBlobPtr;
#endif

class StrBlob { //VER5 Value-like.
#ifndef Pointer_Operations
	friend class StrBlobPtr;
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
		data->push_back(t);
	}

	void pop_back();
	string &front(); // element access
	string &back();
#ifndef Pointer_Operations
	StrBlobPtr begin(); // return StrBlobPtr to the first element
	StrBlobPtr end(); // and one past the last element
#endif

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const; // throws msg if data[i] isn’t valid
};
#endif

#include "12_01_6_1.h" //MINE This header must be here.
#include "12_01_6_util.h"

#ifndef StrBlob_Constructors
StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

#include <iostream>
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

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	test_StrBlob();

	return 0;
}
#endif
