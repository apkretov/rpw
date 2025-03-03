#ifdef ON

#include <cassert> // Second better implementation: exception safe, but ugly // 08-exceptions/myvec-demo/myvec-2.cc @ https://github.com/tilir/cpp-graduate/blob/master/08-exceptions/myvec-demo/myvec-2.cc
#include <iostream>
#include <stdexcept>
#include <utility>
//MINE #include "vld.h"
#include "12_2 controllable.h"
#include "stdafx.h" //MINE
using namespace std; //MINE

int Controllable::control = 5;

template <typename T>
T *safe_copy(const T *src, size_t srcsize, size_t dstsize) {
	assert(srcsize <= dstsize);
	T *dest = new T[dstsize];
	try {
		for (size_t idx = 0; idx != srcsize; ++idx)
			dest[idx] = src[idx];
	}
	catch (...) {
		delete[] dest;
		throw;
	}
	return dest;
}

template <typename T> class MyVector {
	T *arr_ = nullptr;
	size_t size_, used_ = 0;

public:
	explicit MyVector(size_t sz = 0) : arr_(new T[sz]), size_(sz) {}

	MyVector(const MyVector &rhs) {
		arr_ = safe_copy(rhs.arr_, rhs.used_, rhs.used_); //TEST
		size_ = rhs.size_;
		used_ = rhs.used_;
	}

	MyVector(MyVector &&rhs) noexcept : arr_(rhs.arr_), size_(rhs.size_), used_(rhs.used_) {
		rhs.arr_ = nullptr;
		rhs.size_ = 0;
		rhs.used_ = 0;
	}

	MyVector &operator=(MyVector &&rhs) noexcept {
		std::swap(arr_, rhs.arr_);
		std::swap(size_, rhs.size_);
		std::swap(used_, rhs.used_);
	}

	MyVector &operator=(const MyVector &rhs) {
		MyVector tmp(rhs);
		swap(*this, tmp);
		return *this;
	}

	~MyVector() { delete[] arr_; }

	T top() const {
		if (used_ < 1)
			throw out_of_range{};
		return arr_[used_ - 1];
	}

	void pop() {
		if (used_ < 1)
			throw underflow_error{};
		used_ -= 1;
	}

	void push(const T &t) {
		assert(used_ <= size_);
		if (used_ == size_) {
			cout << "Realloc\n";
			size_t newsz = size_ * 2 + 1;
			T *newarr = safe_copy(arr_, size_, newsz);
			delete[] arr_;
			arr_ = newarr;
			size_ = newsz;
			assert(used_ < size_);
		}

		arr_[used_] = t;
		++used_;
	}

	size_t size() const { return used_; }
	size_t capacity() const { return size_; }
};

void test1() {
	Controllable c1, c2, c3;
	MyVector<Controllable> vv1(1);
	vv1.push(c1);
	vv1.push(c2);
	vv1.push(c3);
	cout << "Invoke copy ctor\n";
	MyVector<Controllable> vv2(vv1); // oops
	cout << vv2.size() << endl;
}

int main() {
	PRINT_FILE_LINE(); //MINE

	try {
		test1();
	}
	catch (bad_alloc &) {
		cout << "Exception caught\n";
	}
}
#endif