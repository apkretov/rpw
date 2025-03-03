#pragma once

#include "16_01_4_2.h"

//OFF #define DEBUG_my_unique_ptr

#ifndef	EX_16_28
template <typename T>
class my_unique_ptr {
public:
	my_unique_ptr() = default;
	explicit my_unique_ptr(T *ptr) : p(ptr) {}
	my_unique_ptr(T *ptr, function<void(T *)> d ) : p(ptr), del(d) {}
	my_unique_ptr(const my_unique_ptr &) = delete;
	my_unique_ptr &operator=(const my_unique_ptr &) = delete;
	my_unique_ptr(my_unique_ptr &&) noexcept;
	my_unique_ptr &operator=(my_unique_ptr &&) noexcept;
	~my_unique_ptr();
	T &operator*() const;
	T *get() const;
private:
	T *p{};
	function<void(T *)> del = DebugDelete();
	void delete_ptr();
};

template <typename T>
my_unique_ptr<T>::my_unique_ptr(my_unique_ptr &&s) noexcept : p(s.p), del(s.del) {
#ifdef DEBUG_my_unique_ptr
	cout << "my_unique_ptr move constructor\n";
#endif
	s.p = nullptr;
	s.del = nullptr;
}

template <typename T>
my_unique_ptr<T> &my_unique_ptr<T>::operator=(my_unique_ptr &&rhs) noexcept {
#ifdef DEBUG_my_unique_ptr
	cout << "my_unique_ptr move-assignment operator\n";
#endif
	if (this != &rhs) {
		delete_ptr();

		p = rhs.p;
		del = rhs.del;

		rhs.p = nullptr;
		rhs.del = nullptr;
	}
	return *this;
}

template <typename T>
my_unique_ptr<T>::~my_unique_ptr() {
#ifdef DEBUG_my_unique_ptr
	cout << "my_unique_ptr destructor\n";
#endif
	delete_ptr();
}

template <typename T>
T &my_unique_ptr<T>::operator*() const {
	return *p;
}

template <typename T>
T *my_unique_ptr<T>::get() const {
	return p;
}

template <typename T>
void my_unique_ptr<T>::delete_ptr() {
	del ? del(p) : delete p;
}
#endif
