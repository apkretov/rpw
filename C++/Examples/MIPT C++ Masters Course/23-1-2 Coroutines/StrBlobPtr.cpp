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

std::string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end"); //TEST!
	return (*p)[curr]; // (*p) is the vector to which this object points
}

StrBlobPtr& StrBlobPtr::incr() { // prefix: return a reference to the incremented object
	check(curr, "increment past end of StrBlobPtr"); // if curr already points past the end of the container, can’t increment it
	++curr; // advance the current state
	return *this; //TEST
}

//TEST // these members can’t be defined until StrStrBlob and StrStrBlobPtr are defined
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); } //TEST!

StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); } //TEST!

StrBlobPtr StrBlob::begin() const { return StrBlobPtr(*this); } //MINE The const overloads are declared in StrBlob.h, so they need definitions here too.

StrBlobPtr StrBlob::end() const { return StrBlobPtr(*this, data->size()); } //MINE

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

void print(StrBlob& b) { //MINE
	auto it = b.begin();
	for (StrBlob::size_type i{}; i < b.size(); ++i) {
		std::cout << it.deref() << ' ';
		++it;
	}
	std::cout << '\n';
}
