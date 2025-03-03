#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <initializer_list>
#include <memory>
using std::string;
using std::pair;
using std::initializer_list;
using std::allocator;
using std::cout;

#ifndef Copy_and_Swap_Assignment_Operators_and_Move
#ifndef StrVec_Class_Definition // simplified implementation of the memory allocation strategy for a vector-like class
class StrVec { //VER6
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { // the allocator member is default initialized
		//MINE cout << "Constructor\n"; 
	}
	StrVec(const StrVec &); // copy constructor
	StrVec &operator=(const StrVec &); // copy assignment
#ifndef Move_Operations_Library_Containers_and_Exceptions
	StrVec(StrVec &&) noexcept; // move constructor
	// other members as before
#endif
	StrVec &operator=(StrVec &&) noexcept; //MINE
#ifndef Assignment_Operators
	StrVec &operator=(initializer_list<string>);
	// other members as in § 13.5 (p. 526)
#endif
	~StrVec(); // destructor
	void push_back(const string &); // copy the element
#ifndef Rvalue_References_and_Member_Functions
	void push_back(string &&); // move the element
#endif
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
#ifndef Subscript_Operator
	string &operator[](size_t n) {
		return elements[n]; //TEST!
	}
	const string &operator[](size_t n) const {
		return elements[n];
	}
	// other members as in § 13.5 (p. 526)
#endif
#pragma region Forwarding Parameter Packs
	template <class... Args>
	void emplace_back(Args&&...); //TEST // remaining members as in § 13.5 (p. 526)
#pragma endregion
private:
	static allocator<string> alloc; // allocates the elements

	void chk_n_alloc() { // used by functions that add elements to a StrVec
		if (size() == capacity())
			reallocate();
	}

	// utilities used by the copy constructor, assignment operator, and destructor
	pair<string *, string *> alloc_n_copy(const string *, const string *);
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
	cout << "push_back(const string &s)\n"; //MINE
	chk_n_alloc(); // ensure that there is room for another element
#ifdef ORIG
	alloc.construct(first_free++, s); // construct a copy of s in the element to which first_free points
#elif! CPP20
	construct_at(first_free++, s); // construct a copy of s in the element to which first_free points
#endif
}
#endif

#ifndef Rvalue_References_and_Member_Functions
void StrVec::push_back(string &&s) { //TEST!
	cout << "push_back(string &&)\n"; //MINE
	chk_n_alloc(); // reallocates the StrVec if necessary
#ifdef ORIG
	alloc.construct(first_free++, std::move(s));
#else
	construct_at(first_free++, std::move(s));
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
	cout << "Copy constructor\n"; //MINE
	auto newdata = alloc_n_copy(s.begin(), s.end()); // call alloc_n_copy to allocate exactly as many elements as in s
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() {
	free();
}

StrVec &StrVec::operator=(const StrVec &rhs) {
	cout << "Copy-assignment operator\n"; //MINE
	auto data = alloc_n_copy(rhs.begin(), rhs.end()); // call alloc_n_copy to allocate exactly as many elements as in rhs
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
#endif

#ifndef Move_Iterators
void StrVec::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1; // allocate space for twice as many elements as the current size
	auto first = alloc.allocate(newcapacity);
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first); // move the elements
	free(); // free the old space
	elements = first; // update the pointers
	first_free = last;
	cap = elements + newcapacity;
}
#endif

#ifndef Move_Constructor_and_Move_Assignment
StrVec::StrVec(StrVec &&s) noexcept // move won’t throw any exceptions
	: elements(s.elements), first_free(s.first_free), cap(s.cap) { // member initializers take over the resources in s
	cout << "Move constructor\n"; //MINE
	s.elements = s.first_free = s.cap = nullptr; // leave s in a state in which it is safe to run the destructor
}
#endif

StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
	cout << "Move-assignment operator\n"; //MINE
	if (this != &rhs) { // direct test for self-assignment
		free(); // free existing elements
		elements = rhs.elements; // take over resources from rhs
		first_free = rhs.first_free;
		cap = rhs.cap;
		// leave rhs in a destructible state
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

#ifndef Assignment_Operators
StrVec &StrVec::operator=(initializer_list<string> il) {
	auto data = alloc_n_copy(il.begin(), il.end()); // alloc_n_copy allocates space and copies elements from the given range
	free(); // destroy the elements in this object and free the space
	elements = data.first; // update data members to point to the new space
	first_free = cap = data.second;
	return *this;
}
#endif
#endif

#pragma region Forwarding Parameter Packs
template <class... Args>
inline void StrVec::emplace_back(Args&&... args) {
	chk_n_alloc(); // reallocates the StrVec if necessary
#ifdef ORIG
	alloc.construct(first_free++, std::forward<Args>(args)...);
#else //CPP20
	construct_at(first_free++, std::forward<Args>(args)...); //TEST!
#endif
}
#pragma endregion