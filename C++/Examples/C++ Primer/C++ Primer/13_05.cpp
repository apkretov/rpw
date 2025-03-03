#ifdef ON

#include <iostream>
#include <memory>
#include <utility>
#include "../../stdafx.h"
using namespace std;

#ifndef StrVec_Class_Definition // simplified implementation of the memory allocation strategy for a vector-like class
class StrVec { //VER1 
	friend StrVec getVec(istream &); //MINE
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { // the allocator member is default initialized
		cout << "StrVec constructor\n"; //MINE
	}

	StrVec(const StrVec &); // copy constructor
	StrVec &operator=(const StrVec &); // copy assignment
#ifndef Move_Operations_Library_Containers_and_Exceptions
	StrVec(StrVec &&) noexcept; // move constructor
#endif
#ifndef Move_Assignment_Operator
	StrVec &operator=(StrVec &&) noexcept; //MINE
#endif
	~StrVec(); // destructor
	void push_back(const string &); // copy the element

	size_t size() const {
		return first_free - elements;
	}

	size_t capacity() const {
		return cap - elements;
	}
	string *begin() const {
		return elements;
	}

	string *end() const {
		return first_free;
	}
	// ...
private:
	static allocator<string> alloc; // allocates the elements

	void chk_n_alloc() { // used by functions that add elements to a StrVec
		if (size() == capacity())
			reallocate();
	}

	pair<string *, string *> alloc_n_copy(const string *, const string *); // utilities used by the copy constructor, assignment operator, and destructor
	void free(); // destroy the elements and free the space
	void reallocate(); // get more space and copy the existing elements
	string *elements; // pointer to the first element in the array
	string *first_free; // pointer to the first free element in the array
	string *cap; // pointer to one past the end of the array
};

allocator<string> StrVec::alloc; // alloc must be defined in the StrVec implmentation file
#endif

#ifndef Using_construct
void StrVec::push_back(const string &s) {
	chk_n_alloc(); // ensure that there is room for another element
#ifdef ORIG
	alloc.construct(first_free++, s); // construct a copy of s in the element to which first_free points
#elif! CPP20
	/*
	you.com
	In C++20, the std::construct_at function was introduced as a standardized way to construct an object at a specific memory location.It is part of the <memory> header and can be used to construct an object without relying on the construct member function of std::allocator.
	By using construct_at(first_free++, s), the code correctly constructs a copy of s at the first_free pointer, ensuring that the memory is properly initialized with the desired object.
	Please note that std::construct_at is available in C++20 and later versions.If you are using an older version of C++, you can use the std::uninitialized_copy function
	*/
	construct_at(first_free++, s); // construct a copy of s in the element to which first_free points
#endif
}
#endif

#ifndef The_alloc_n_copy_Member
pair<string *, string *> StrVec::alloc_n_copy(const string *b, const string *e) { // allocate space to hold as many elements as are in the range
	auto data = alloc.allocate(e - b);
	return {data, uninitialized_copy(b, e, data)}; // initialize and return a pair constructed from data and the value returned by uninitialized_copy
}
#endif

#ifndef The_free_Member
void StrVec::free() {
	if (elements) { // may not pass deallocate a 0 pointer; if elements is 0, there’s no work to do
		for (auto p = first_free; p != elements; /* empty */) // destroy the old elements in reverse order
#ifdef ORIG
			alloc.destroy(--p);
#elif! CPP20
			destroy_at(--p);
#endif
		alloc.deallocate(elements, cap - elements);
	}
}
#endif

#ifndef Copy_Control_Members
StrVec::StrVec(const StrVec &s) {
	cout << "StrVec copy-constructor\n"; //MINE
	auto newdata = alloc_n_copy(s.begin(), s.end()); // call alloc_n_copy to allocate exactly as many elements as in s
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() {
	free();
}

StrVec &StrVec::operator=(const StrVec &rhs) {
	cout << "StrVec copy-assignment operator\n"; //MINE
	auto data = alloc_n_copy(rhs.begin(), rhs.end()); // call alloc_n_copy to allocate exactly as many elements as in rhs
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
#endif

#ifndef The_reallocate_Member
void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1; // we’ll allocate space for twice as many elements as the current size
	auto newdata = alloc.allocate(newcapacity); // allocate new memory
	// move the data from the old memory to the new
	auto dest = newdata; // points to the next free position in the new array
	auto elem = elements; // points to the next element in the old array

	for (size_t i = 0; i != size(); ++i)
#ifdef ORIG 
		alloc.construct(dest++, std::move(*elem++));
#elif! CPP20
		construct_at(dest++, std::move(*elem++)); //TEST!
#endif
	free(); // free the old space once we’ve moved the elements

	elements = newdata; // update our data structure to point to the new elements
	first_free = dest;
	cap = elements + newcapacity;
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();

	return 0;
}
#endif

#ifdef EX_13_44

#include "13_05.h"
using namespace std;

template <typename T>
void print(const string &var, const T &s) {
	cout << var << ":\t" << s << '\t' << s.size() << '\t' << s.capacity() << '\n';
}

#define STRINGIZE(x) #x

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	String s1("test test");
	print(STRINGIZE(s1), s1);

	s1 = s1;
	print(STRINGIZE(s1), s1);

	const String s2;
	print(STRINGIZE(s2), s2);

	const String s3(s1);
	print(STRINGIZE(s3), s3);

	String s4(s2);
	print(STRINGIZE(s4), s4);
	s4 = s1;
	print(STRINGIZE(s4), s4);
	s4.push_back(" push");
	print(STRINGIZE(s4), s4);

	String s5;
	print(STRINGIZE(s5), s5);
	s5.push_back("push");
	print(STRINGIZE(s5), s5);
	s5.push_back(" push");
	print(STRINGIZE(s5), s5);
	s5.push_back(" push");

	return 0;
}
#endif

#ifdef EX_13_44_2 // ch13/ex13_44_47.h @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch13/ex13_44_47.h // ch13/ex13_44_47.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch13/ex13_44_47.cpp
#include <memory>

//MINE
#include <iostream>
using namespace std;

class String {
public:
	String() : String("") {}
	String(const char *);
	String(const String &);
	String &operator=(const String &);
	~String();

	const char *c_str() const { return elements; }
	size_t size() const { return end - elements; }
	size_t length() const { return end - elements - 1; }

private:
	std::pair<char *, char *> alloc_n_copy(const char *, const char *);
	void range_initializer(const char *, const char *);
	void free();

private:
	char *elements;
	char *end;
	std::allocator<char> alloc;
};

#include <algorithm>
#include <iostream>

std::pair<char *, char *>
String::alloc_n_copy(const char *b, const char *e) {
	auto str = alloc.allocate(e - b);
	return{str, std::uninitialized_copy(b, e, str)};
}

void String::range_initializer(const char *first, const char *last) {
	auto newstr = alloc_n_copy(first, last);
	elements = newstr.first;
	end = newstr.second;
}

String::String(const char *s) {
	char *sl = const_cast<char *>(s);
	while (*sl)
		++sl;
	range_initializer(s, ++sl);
}

String::String(const String &rhs) {
	range_initializer(rhs.elements, rhs.end);
	std::cout << "copy constructor" << std::endl;
}

void String::free() {
	if (elements) {
#ifdef ORIG
		std::for_each(elements, end, [this](char &c) { alloc.destroy(&c); });
#else
		std::for_each(elements, end, [this](char &c) { destroy_at(&c); });
#endif
		alloc.deallocate(elements, end - elements);
	}
}

String::~String() {
	free();
}

String &String::operator = (const String &rhs) {
	auto newstr = alloc_n_copy(rhs.elements, rhs.end);
	free();
	elements = newstr.first;
	end = newstr.second;
	std::cout << "copy-assignment" << std::endl;
	return *this;
}

int main(int argc, char *argv[]) { //MINE
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	String s("test");
	cout << *s.c_str() << '\n';

	return 0;
}
#endif

#ifdef EX_13_44_3 // ch13/13.44/String.h @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch13/13.44/String.h

#include <initializer_list>
#include <memory>
#include <string>

class String {
public:
	typedef size_t size_type;
	typedef char *iterator;
	typedef const char *const_iterator;
	typedef char &reference;
	typedef const char &const_reference;

	String() : first_elem(nullptr), first_free(nullptr), cap(nullptr) {}
	String(const_iterator);
	String(std::initializer_list<char>);

	String(const String &);
	~String();
	String &operator=(const String &);
	String &operator=(const_iterator);

	void push_back(const_reference);
	void pop_back();

	void reserve(size_type);
	void resize(size_type, const_reference = char());
	// default value for parameter put in declaration

	bool empty() const { return cbegin() == cend(); }
	size_type size() const { return first_free - first_elem; }
	size_type capacity() const { return cap - first_elem; }

	iterator begin() { return first_elem; }
	iterator end() { return first_free; }
	const_iterator begin() const { return first_elem; }
	const_iterator end() const { return first_free; }
	const_iterator cbegin() const { return begin(); }
	const_iterator cend() const { return end(); }

	std::string str() const;

private:
	static std::allocator<char> alloc;

	iterator first_elem;
	iterator first_free;
	iterator cap;
	// These three pointer should be either all `nullptr`s or all pointing to the
	// same memory block. (Class invariant)

	void reallocate(size_type);
	void free();
};


// ch13/13.44/String.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch13/13.44/String.cpp
//OFF #include "String.h"

std::allocator<char> String::alloc;

String::String(const_iterator ci) : String() {
	while (ci && *ci != '\0')
		push_back(*ci++);
}

String::String(std::initializer_list<char> il) : String() {
	for (const auto &c : il)
		push_back(c);
}

void String::push_back(const_reference c) {
	if (size() == capacity())
		reallocate(empty() ? 1 : 2 * capacity());
#ifdef ORIG
	alloc.construct(first_free++, c);
#else
	construct_at(first_free++, c);
#endif
}

void String::pop_back() {
	if (!empty())
#ifdef ORIG
		alloc.destroy(--first_free);
#else
		destroy_at(--first_free);
#endif
}

void String::reserve(size_type n) {
	if (n > capacity()) {
		reallocate(n);
	}
}

void String::resize(size_type n, const_reference c) {
	if (n > size()) {
		for (int i = n - size(); i > 0; --i)
			push_back(c);
	} else if (n < size()) {
		for (int i = size() - n; i > 0; --i)
			pop_back();
	}
}

void String::reallocate(size_type n) {
	auto new_first_elem = alloc.allocate(n);
	auto new_first_free = new_first_elem;
	for (auto it = begin(); it != end(); ++it)
#ifdef ORIG
		alloc.construct(new_first_free++, std::move(*it));
#else
		construct_at(new_first_free++, std::move(*it));
#endif
	// the above three lines of code can be replaced by the following code:
	//auto new_first_free = std::uninitialized_copy(
	//    std::make_move_iterator(begin()),
	//    std::make_move_iterator(end()), new_first_elem);
	free();
	first_elem = new_first_elem;
	first_free = new_first_free;
	cap = first_elem + n;
}

void String::free() {
	while (!empty())
#ifdef ORIG
		alloc.destroy(--first_free);
#else
		destroy_at(--first_free);
#endif
	alloc.deallocate(first_elem, capacity());
	first_elem = first_free = cap = nullptr;
}

String::String(const String &rhs) {
	first_elem = alloc.allocate(rhs.size());
	first_free = cap = std::uninitialized_copy(rhs.begin(), rhs.end(),
		first_elem);
}

String::~String() {
	free();
}

String &String::operator=(const String &rhs) {
	auto new_first_elem = alloc.allocate(rhs.size());
	auto new_first_free = std::uninitialized_copy(rhs.begin(), rhs.end(),
		new_first_elem);
	free();
	first_elem = new_first_elem;
	first_free = cap = new_first_free;
	return *this;
}

String &String::operator=(const_iterator ci) {
	*this = String(ci);
	return *this;
}

std::string String::str() const {
	return std::string(cbegin(), cend());
}

// ch13/13.44/13.44.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch13/13.44/13.44.cpp
#include <iostream>
//OFF #include "String.h"

void print(const String &s) {
	std::cout << "<" << &s << ">:<" << s.str() << "> size: "
		<< s.size() << " capacity: " << s.capacity() << std::endl;
}

int main() {
	String s1; print(s1);
	s1.pop_back(); print(s1);
	s1.push_back('a'); print(s1);
	s1.push_back('b'); print(s1);
	s1.push_back('c'); print(s1);
	s1.push_back('d'); print(s1);
	{
		String s2 = "s2"; print(s2);
		s2 = "s3"; print(s2);
#ifdef ORIG
		char *cs = "def";
#else
		const char *cs = "def";
#endif
		s2 = cs; print(s2);
		s2 = s1; print(s2);
	}
	print(s1);
	s1.pop_back(); print(s1);

	s1.reserve(s1.capacity() / 2); print(s1);
	s1.reserve(s1.capacity() * 2); print(s1);

	s1.resize(s1.size() + 6); print(s1);
	s1.resize(s1.size() + 6, 'x'); print(s1);
	s1.resize(s1.size() - 6); print(s1);
	s1.resize(s1.size() - 6, 'x'); print(s1);

	String s2{'m', 'n', 'p', 'q', 'r'}; print(s2);
	String s3 = {'m', 'n', 'p', 'q', 'r'}; print(s3);

	return 0;
}
#endif