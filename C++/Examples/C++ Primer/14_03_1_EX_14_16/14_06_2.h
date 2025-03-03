#pragma once

#ifndef Defining_Prefix_Increment_Decrement_Operators
StrBlobPtr &StrBlobPtr::operator++() { // prefix: return a reference to the incremented/decremented object
	check(curr, "increment past end of StrBlobPtr"); // if curr already points past the end of the container, can’t increment it
	++curr; // advance the current state
	return *this;
}

StrBlobPtr &StrBlobPtr::operator--() {
	--curr; //TEST! // if curr is zero, decrementing it will yield an invalid subscript // move the current state back one element
	check(curr, "decrement past begin of StrBlobPtr");
	return *this;
}
#endif

#ifndef Differentiating_Prefix_and_Postfix_Operators
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
#endif

void print(StrBlob &b) { //MINE
	auto it = b.begin();
	for (StrBlob::size_type i{}; i < b.size(); ++i) {
		std::cout << it.deref() << ' ';
		++it;
	}
	std::cout << '\n';
}
