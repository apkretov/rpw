#include "StrBlob.h"
#include <iostream>

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}
StrBlob::StrBlob(const StrBlob& b) : data(std::make_shared<std::vector<std::string>>(*b.data)) {}

StrBlob& StrBlob::operator=(const StrBlob& b) {
	data = std::make_shared<std::vector<std::string>>(*b.data);
	return *this;
}

void StrBlob::check(size_type i, const std::string& msg) const {
	if (i > data->size())
		throw std::out_of_range(msg);
}

std::string& StrBlob::front() {
	check(0, "front on empty StrBlob"); // if the vector is empty, check will throw
	return data->front();
}

std::string& StrBlob::back() {
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::push_back(const std::string& t) { // add and remove elements
	std::cout << "push_back(const string &)\n";
	data->push_back(t);
}

void StrBlob::push_back(std::string&& t) {
	std::cout << "push_back(string &&)\n";
	data->push_back(std::move(t));
}

void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

StrBlobPtr StrBlob::begin() const { return StrBlobPtr(*this); } //MINE The const overloads are declared in StrBlob.h, so they need definitions here too.

StrBlobPtr StrBlob::end() const { return StrBlobPtr(*this, data->size()); } //MINE

bool operator==(const StrBlob& lhs, const StrBlob& rhs) { return *lhs.data == *rhs.data; }

bool operator!=(const StrBlob& lhs, const StrBlob& rhs) { return !(lhs == rhs); }
