#include "StrBlobPtr.h"
#include "StrBlob.h" //MINE This translation unit defines StrBlob members, so it needs StrBlob to be complete.

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_t i, const std::string& msg) const {
	auto ret = wptr.lock(); // is the std::vector still around?

	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr"); //TEST!
	if (i >= ret->size())
		throw std::out_of_range(msg); //TEST!

	return ret; // otherwise, return a shared_ptr to the vector
}

StrBlobPtr& StrBlobPtr::operator++() { // prefix: return a reference to the incremented/decremented object
	check(curr, "increment past end of StrBlobPtr"); // if curr already points past the end of the container, can’t increment it
	++curr; // advance the current state
	return *this;
}

StrBlobPtr& StrBlobPtr::operator--() {
	--curr; //TEST! // if curr is zero, decrementing it will yield an invalid subscript // move the current state back one element
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) { // postfix: increment/decrement the object but return the unchanged value
	//TEST! // no check needed here; the call to prefix increment will do the check
	StrBlobPtr ret = *this; // save the current value
	++*this; //TEST! // advance one element; prefix ++ checks the increment
	return ret; // return the saved state
}

StrBlobPtr StrBlobPtr::operator--(int) {
	// no check needed here; the call to prefix decrement will do the check
	StrBlobPtr ret = *this; // save the current value
	--*this; // move backward one element; prefix -- checks the decrement
	return ret; // return the saved state
}

std::string& StrBlobPtr::operator*() const { //TEST
	auto p = check(curr, "dereference past end");
	return (*p)[curr]; // (*p) is the vector to which this object points
}

bool StrBlobPtr::operator==(const StrBlobPtr& other) const { return other.curr == curr; }

bool StrBlobPtr::operator!=(const StrBlobPtr& other) const { return !operator==(other); }

std::ostream& operator<<(std::ostream& os, const StrBlob& b) { //MINE
	#ifdef ITERATOR_BASED
	for (auto it = b.begin(); it != b.end(); ++it)
		os << *it << ' ';
	#else RANGE_BASED
	for (const std::string& it : b)
		os << it << ' ';
	#endif //RANGE_BASED
	return os;
}
