#pragma once

#ifndef EX_13_44

#include <iostream>

class String {
	friend std::ostream &operator<<(std::ostream &, const String &);
public:
	explicit String(const char *const = "");
	String(const String &);
	String &operator=(const String &);
	~String();
	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	void push_back(const char *const);
private:
	char *elements{}, *first_free{}, *cap{};
	size_t lencap, lensz;
	void free();
	std::pair<char *, char *> realloc(const String &, const size_t);
	static std::allocator<char> alloc;
};

std::allocator<char> String::alloc;

String::String(const char *const s) : lencap(strlen(s)), lensz(lencap) {
	std::cout << "Constructor\n";
	if (lencap > 0) {
		elements = alloc.allocate(lencap);
		cap = first_free = std::uninitialized_copy(s, s + lencap, elements);
	}
}

String::String(const String &s) {
	std::cout << "Copy constructor\n";

	if (s.size() > 0) {
		auto p = realloc(s, s.size());
		elements = p.first;
		cap = first_free = p.second;
		lencap = lensz = first_free - elements;
	}
}

String &String::operator=(const String &rhs) {
	std::cout << "Copy-assignment operator\n";

	if (rhs.size() > 0) {
		auto p = realloc(rhs, rhs.size());
		free();
		elements = p.first;
		cap = first_free = p.second;
		lencap = lensz = first_free - elements;
	}

	return *this;
}

String::~String() {
	free();
}

size_t String::size() const {
	return lensz; // return first_free - elements; does not work for moving.
}

size_t String::capacity() const {
	return lencap; // return cap - elements; does not work for moving.
}

bool String::empty() const {
	return !(bool)size(); // return elements == first_free; does not work for moving.
}

void String::free() {
	if (!empty()) {
		while (lensz-- > 0) // while (first_free != elements) does not work for moving.
			std::destroy_at(first_free--);
		alloc.deallocate(elements, capacity());
	}
	elements = first_free = cap = nullptr;
	lencap = 0;
}

std::pair<char *, char *> String::realloc(const String &s, const size_t sz) {
	auto elem = String::alloc.allocate(sz);
	auto first = std::uninitialized_copy(s.elements, s.first_free, elem);
	return {elem, first};
}

void String::push_back(const char *const s) {
	auto len = strlen(s);
	if (first_free + len > cap) {
		auto newcap = size() + len * 2;
		auto p = realloc(*this, newcap);
		free();
		elements = p.first;
		first_free = p.second;
		cap = elements + newcap;
		lencap = newcap;
	}
	first_free = std::uninitialized_copy(s, s + len, first_free);
	lensz = first_free - elements;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
	for (auto p = s.elements; p != s.first_free; ++p)
		out << *p;
	return out;
}
#endif