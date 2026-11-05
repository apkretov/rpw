#include "StrBlob.h"

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}
StrBlob::StrBlob(const StrBlob& b) : data(make_shared<vector<string>>(*b.data)) {}

StrBlob& StrBlob::operator=(const StrBlob& b) {
	data = make_shared<vector<string>>(*b.data);
	return *this;
}

void StrBlob::check(size_type i, const string& msg) const {
	if (i > data->size())
		throw out_of_range(msg);
}

string& StrBlob::front() {
	check(0, "front on empty StrBlob"); // if the vector is empty, check will throw
	return data->front();
}

string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

bool operator==(const StrBlob& lhs, const StrBlob& rhs) { return *lhs.data == *rhs.data; }

bool operator!=(const StrBlob& lhs, const StrBlob& rhs) { return !(lhs == rhs); }
