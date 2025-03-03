#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

//ORIG #include <DebugDelete.h>
#include "delete.hpp" //MINE

template <typename, typename> // forward declarations for friendship
class unique_pointer;

template <typename T, typename D>
void swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs);

//ORIG template <typename T, typename D = DebugDelete>
template <typename T, typename D = cp5::Delete> //MINE
class unique_pointer {
	friend void swap<T, D>(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs);

public:
	unique_pointer(const unique_pointer &) = delete; // preventing copy and assignment
	unique_pointer &operator = (const unique_pointer &) = delete;

	unique_pointer() = default; // default constructor and one taking T*
	explicit unique_pointer(T *up) : ptr(up) {}

	unique_pointer(unique_pointer &&up) noexcept : ptr(up.ptr) { // move constructor
		up.ptr = nullptr;
	}

	unique_pointer &operator =(unique_pointer &&rhs) noexcept; // move assignment
	unique_pointer &operator =(std::nullptr_t n) noexcept;  // std::nullptr_t assignment

	T &operator  *() const { return *ptr; } // operator overloaded :  *  ->  bool
	T *operator ->() const { return &this->operator *(); }
	operator bool() const { return ptr ? true : false; }

	T *get() const noexcept { return ptr; } // return the underlying pointer

	void swap(unique_pointer<T, D> &rhs) { ::swap(*this, rhs); } // swap member using swap friend

	void reset()     noexcept { deleter(ptr); ptr = nullptr; } // free and make it point to nullptr or to p's pointee.
	void reset(T *p) noexcept { deleter(ptr); ptr = p; }

	T *release(); // return ptr and make ptr point to nullptr.

	~unique_pointer() {
		deleter(ptr);
	}
private:
	T *ptr = nullptr;
	D  deleter = D();
};

template <typename T, typename D> // swap
inline void
swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs) {
	using std::swap;
	swap(lhs.ptr, rhs.ptr);
	swap(lhs.deleter, rhs.deleter);
}

template <typename T, typename D> // move assignment
inline unique_pointer<T, D> &
unique_pointer<T, D>::operator =(unique_pointer &&rhs) noexcept {
	if (this->ptr != rhs.ptr) {
		deleter(ptr);
		ptr = nullptr;
		::swap(*this, rhs);
	}
	return *this;
}

template <typename T, typename D> // std::nullptr_t assignment
inline unique_pointer<T, D> &
unique_pointer<T, D>::operator =(std::nullptr_t n) noexcept {
	if (n == nullptr) {
		deleter(ptr);   ptr = nullptr;
	}
	return *this;
}

template <typename T, typename D> // relinquish control by returning ptr and making ptr point to nullptr.
inline T *unique_pointer<T, D>::release() {
	T *ret = ptr;
	ptr = nullptr;
	return ret;
}
#endif
