#pragma once

#ifndef Checked_Pointer_Class 
std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_t i, const std::string &msg) const {
	auto ret = wptr.lock(); // is the std::vector still around?

	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr"); //TEST!
	if (i >= ret->size())
		throw std::out_of_range(msg); //TEST!

	return ret; // otherwise, return a shared_ptr to the vector
}
#endif

#ifndef Pointer_Operations
std::string &StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end"); //TEST!
	return (*p)[curr]; // (*p) is the vector to which this object points
}

StrBlobPtr &StrBlobPtr::incr() { // prefix: return a reference to the incremented object
	check(curr, "increment past end of StrBlobPtr"); // if curr already points past the end of the container, can’t increment it
	++curr; // advance the current state
	return *this; //TEST
}

//TEST // these members can’t be defined until StrStrBlob and StrStrBlobPtr are defined
#ifndef EX_12_32
StrBlobPtr StrBlob::begin() {
#else
StrBlobPtr StrBlob::begin() const {
#endif
	return StrBlobPtr(*this); //TEST!
}

#ifndef EX_12_32
StrBlobPtr StrBlob::end() {
#else
StrBlobPtr StrBlob::end() const {
#endif
	return StrBlobPtr(*this, data->size()); //TEST!
}
#endif