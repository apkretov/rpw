#pragma once

#ifndef StrBlob_Constructors
StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
#endif

#ifndef Element_Access_Members
void StrBlob::check(size_type i, const string &msg) const {
	if (i > data->size())
		throw out_of_range(msg);
}

string &StrBlob::front() const {
	check(0, "front on empty StrBlob"); // if the vector is empty, check will throw
	return data->front();
}

string &StrBlob::back() const {
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back() const {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
#endif
