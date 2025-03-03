#pragma once

#include <iostream>
#include <initializer_list>
#include <utility>
#include <memory>
using std::pair;
using std::initializer_list;
using std::allocator;
using std::cout;

#pragma region EX_16_16
template <typename T>
class Vec { //VER2
public:
	Vec() = default;
	explicit Vec(initializer_list<T> il);
	Vec(const Vec &); // copy constructor
	Vec &operator=(const Vec &); // copy assignment
	Vec(Vec &&) noexcept; // move constructor
	Vec &operator=(Vec &&) noexcept; //MINE
	Vec &operator=(initializer_list<T>);
	~Vec(); // destructor
	void push_back(const T &); // copy the element
	void push_back(T &&); // move the element
#pragma region EX_16_58
	template <class... Args>
	void emplace_back(Args&&...);
#pragma endregion

	size_t size() const {
		return first_free - elements;
	}

	size_t capacity() const {
		return cap - elements;
	}

	T *begin() const {
		return elements;
	}

	T *end() const {
		return first_free;
	}

	T &operator[](size_t n) {
		return elements[n];
	}
	const T &operator[](size_t n) const {
		return elements[n];
	}

private:
	static allocator<T> alloc; // allocates the elements

	void chk_n_alloc() { // used by functions that add elements to a Vec
		if (size() == capacity())
			reallocate();
	}

	pair<T *, T *> alloc_n_copy(const T *, const T *) const; // utilities used by the copy constructor, assignment operator, and destructor
	void free(); // destroy the elements and free the space
	void reallocate(); // get more space and copy the existing elements
	T *elements = nullptr; // pointer to the first element in the array
	T *first_free = nullptr; // pointer to the first free element in the array
	T *cap = nullptr; // pointer to one past the end of the array
};

template <typename T>
allocator<T> Vec<T>::alloc; // alloc must be defined in the Vec implementation file

template <typename T>
void Vec<T>::push_back(const T &s) {
	cout << "push_back(const T &)\n"; //MINE
	chk_n_alloc(); // ensure that there is room for another element
	construct_at(first_free++, s); //ORIG: alloc.construct(first_free++, s); // construct a copy of s in the element to which first_free points
}

template <typename T>
void Vec<T>::push_back(T &&s) {
	cout << "push_back(T &&)\n"; //MINE
	chk_n_alloc(); // ensure that there is room for another element
	construct_at(first_free++, std::move(s));
}

#pragma region EX_16_58
template <typename T>
template <typename... Args>
inline void Vec<T>::emplace_back(Args&&... args) {
	chk_n_alloc(); // reallocates the StrVec if necessary
	construct_at(first_free++, std::forward<Args>(args)...);
}
#pragma endregion

template <typename T>
pair<T *, T *> Vec<T>::alloc_n_copy(const T *b, const T *e) const {
	auto data = alloc.allocate(e - b); // allocate space to hold as many elements as are in the range
	return {data, uninitialized_copy(b, e, data)}; // initialize and return a pair constructed from data and the value returned by uninitialized_copy
}

template <typename T>
void Vec<T>::free() {
	if (elements) { // may not pass deallocate a 0 pointer; if elements is 0, there’s no work to do
		for (auto p = first_free; p != elements; /* empty */) // destroy the old elements in reverse order
			std::destroy_at(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

template <typename T>
Vec<T>::Vec(initializer_list<T> il) {
	cout << "Constructor\n"; //MINE
	auto [first, second] = alloc_n_copy(il.begin(), il.end()); // alloc_n_copy allocates space and copies elements from the given range
	elements = first; // update data members to point to the new space
	first_free = cap = second;
}

template <typename T>
Vec<T>::Vec(const Vec &s) {
	cout << "Copy constructor\n"; //MINE
	auto [first, second] = alloc_n_copy(s.begin(), s.end()); // call alloc_n_copy to allocate exactly as many elements as in s
	elements = first;
	first_free = cap = second;
}

template <typename T>
Vec<T>::~Vec() {
	free();
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec &rhs) {
	cout << "Copy-assignment operator\n"; //MINE
	auto [first, second] = alloc_n_copy(rhs.begin(), rhs.end()); // call alloc_n_copy to allocate exactly as many elements as in rhs
	free();
	elements = first;
	first_free = cap = second;
	return *this;
}

template <typename T>
void Vec<T>::reallocate() {
	auto newcapacity = size() ? 2 * size() : 1; // allocate space for twice as many elements as the current size
	auto first = alloc.allocate(newcapacity);
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first); // move the elements
	free(); // free the old space
	elements = first; // update the pointers
	first_free = last;
	cap = elements + newcapacity;
}

template <typename T>
Vec<T>::Vec(Vec &&s) noexcept // move won’t throw any exceptions
	: elements(s.elements), first_free(s.first_free), cap(s.cap) { // member initializers take over the resources in s
	cout << "Move constructor\n"; //MINE
	s.elements = s.first_free = s.cap = nullptr; // leave s in a state in which it is safe to run the destructor
}

template <typename T>
Vec<T> &Vec<T>::operator=(Vec &&rhs) noexcept {
	cout << "Move-assignment operator\n"; //MINE
	if (this != &rhs) { // direct test for self-assignment
		free(); // free existing elements
		elements = rhs.elements; // take over resources from rhs
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr; // leave rhs in a destructible state
	}
	return *this;
}

template <typename T>
Vec<T> &Vec<T>::operator=(initializer_list<T> il) {
	auto [first, second] = alloc_n_copy(il.begin(), il.end()); // alloc_n_copy allocates space and copies elements from the given range
	free(); // destroy the elements in this object and free the space
	elements = first; // update data members to point to the new space
	first_free = cap = second;
	return *this;
}
#pragma endregion