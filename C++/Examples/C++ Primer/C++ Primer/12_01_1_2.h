#pragma once

#include <stdexcept>
using namespace std;

#ifndef StrBlob_Constructors
StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {} //TEST!
#endif

#ifndef Element_Access_Members
void StrBlob::check(size_type i, const string &msg) const {
	if (i > data->size())
		throw out_of_range(msg); //TEST!
}

void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
#endif