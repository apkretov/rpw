#pragma once

#include <functional>
#include <memory>
using std::function;
using std::allocator;
using std::construct_at;
using std::destroy_at;

//OFF #define DEBUG_my_shared_ptr

#ifndef EX_16_61
#pragma region EX_16_28
template <typename T>
class my_shared_ptr { //VER2
public:
	my_shared_ptr() = default;
	explicit my_shared_ptr(T *ptr, function<void(T *)> d = nullptr) : p(ptr), del(d) {}
	my_shared_ptr(const my_shared_ptr &);
	my_shared_ptr &operator=(const my_shared_ptr &);
	my_shared_ptr(my_shared_ptr &&) noexcept;
	my_shared_ptr &operator=(my_shared_ptr &&) noexcept;
	~my_shared_ptr();
	T &operator*() const;
	size_t use_count() const;
	T *get() const;
private:
	T *p{};
	function<void(T *)> del{};
	size_t *use = new size_t(1); // member to keep track of how many objects share *p
	void delete_ptr();
};

template <typename T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr &s) : p(s.p), del(s.del), use(s.use) {
	++*use;
}

template <typename T>
my_shared_ptr<T> &my_shared_ptr<T>::operator=(const my_shared_ptr &rhs) {
	++*rhs.use;
	delete_ptr();

	p = rhs.p;
	del = rhs.del;
	use = rhs.use;

	return *this;
}

template <typename T>
my_shared_ptr<T>::my_shared_ptr(my_shared_ptr &&s) noexcept : p(s.p), del(s.del), use(s.use) {
	s.p = nullptr;
	s.del = nullptr;
	s.use = nullptr;
}

template <typename T>
my_shared_ptr<T> &my_shared_ptr<T>::operator=(my_shared_ptr &&rhs) noexcept {
	if (this != &rhs) {
		p = rhs.p;
		del = rhs.del;
		use = rhs.use;

		rhs.p = nullptr;
		rhs.del = nullptr;
		rhs.use = nullptr;
	}
	return *this;
}

template <typename T>
my_shared_ptr<T>::~my_shared_ptr() {
#ifdef DEBUG_my_shared_ptr
	cout << "\nmy_shared_ptr destructor";
#endif
	delete_ptr();
}

template <typename T>
T &my_shared_ptr<T>::operator*() const {
	return *p;
}

template <typename T>
size_t my_shared_ptr<T>::use_count() const {
	return *use;
}

template <typename T>
T *my_shared_ptr<T>::get() const {
	return p;
}

template <typename T>
void my_shared_ptr<T>::delete_ptr() {
	if (p != nullptr) //TEST!!
		if (--*use == 0) {
			del ? del(p) : delete p;
			delete use;
		}
}
#pragma endregion

#pragma region EX_16_61
template <typename T, typename... Args>
my_shared_ptr<T> my_make_shared(Args&&... args) {
#ifdef MINE
	allocator<T> alloc; // allocates the elements
	auto p = alloc.allocate(1); // allocate space to one element of type T.
	construct_at(p, std::forward<Args>(args)...);
#else // ch16/ex16.60.61/main.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch16/ex16.60.61/main.cpp
	auto p = new T(std::forward<Args>(args)...);
#endif
	return my_shared_ptr<T>(p);
}
#pragma endregion
#endif
