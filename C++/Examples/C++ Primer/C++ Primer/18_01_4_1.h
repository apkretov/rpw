#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using std::bad_alloc;
using std::cerr;
using std::out_of_range;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;
using std::weak_ptr;

template <typename> class Blob; //MINE

#ifndef Simplifying_Use_of_a_Template_Class_Name_inside_Class_Code
template <typename T> // BlobPtr throws an exception on attempts to access a nonexistent element
class BlobPtr { //VER3
public:
#pragma region EX_18_08
	BlobPtr() noexcept(false) : curr(0) {}
#pragma endregion
#pragma region EX_18_07
#pragma region EX_18_08
	BlobPtr(Blob<T> &a, size_t sz = 0) noexcept(false) try : wptr(a.data), curr(sz) {/*empty*/}
#pragma endregion
	catch (const bad_alloc &e) {
		cerr << "Error : " << e.what() << '\n';
	}
#pragma endregion
	T &operator*() const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr]; // (*p) is the vector to which this object points
	}
#ifndef _1
	BlobPtr &operator++(); // increment and decrement // prefix operators
	BlobPtr &operator--();
#else // That is, it is as if we had written:
	BlobPtr<T> &operator++();
	BlobPtr<T> &operator--();
#endif
	BlobPtr operator++(int); // postfix operators //MINE
private:
	shared_ptr<vector<T>> check(size_t, const string &) const; // check returns a shared_ptr to the vector if the check succeeds
	weak_ptr<vector<T>> wptr; // store a weak_ptr, which means the underlying vector might be destroyed
	size_t curr; // current position within the array
};
#endif

#ifndef Using_a_Class_Template_Name_outside_the_Class_Template_Body
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) { // postfix: increment/decrement the object but return the unchanged value
#ifndef _1 // no check needed here; the call to prefix increment will do the check
	BlobPtr ret = *this; // save the current value
#else // the definition of ret is as if we had written:
	BlobPtr<T> ret = *this;
#endif
	++ * this; // advance one element; prefix ++ checks the increment
	return ret; // return the saved state
}
#endif

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++() { // prefix: return a reference to the incremented/decremented object //MINE
	check(curr, "increment past end of StrBlobPtr"); // if curr already points past the end of the container, can’t increment it
	++curr; // advance the current state
	return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--() { //MINE
	--curr; // if curr is zero, decrementing it will yield an invalid subscript // move the current state back one element
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}

template <typename T>
shared_ptr<vector<T>> BlobPtr<T>::check(size_t i, const string &msg) const { //MINE
	auto ret = wptr.lock(); // is the std::vector still around?

	if (!ret)
		throw runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);

	return ret; // otherwise, return a shared_ptr to the vector
}
