#pragma once

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>
using std::string;
using std::vector;
using std::initializer_list;
using std::shared_ptr;
using std::make_shared;
using std::out_of_range;

#ifndef Defining_a_Class_Template
template <typename T> 
class Blob { //VER1
public:
	using value_type = T; //OIRG typedef T value_type;
	using size_type = typename vector<T>::size_type; //ORIG typedef typename vector<T>::size_type size_type;
	Blob(); // constructors
	explicit Blob(initializer_list<T> il); //ORIG Blob(initializer_list<T> il);
	
	size_type size() const { // number of elements in the Blob
		return data->size();
	}

	bool empty() const {
		return data->empty();
	}

	void push_back(const T &t) { // add and remove elements
		data->push_back(t);
	}

	void push_back(T &&t) { // move version; see § 13.6.3 (p. 548)
		data->push_back(std::move(t));
	}

	void pop_back();
	T &back(); // element access
	T &operator[](size_type i); // defined in § 14.5 (p. 566)
private:
	shared_ptr<vector<T>> data;
	void check(size_type i, const string &msg) const; // throws msg if	data[i] isn’t valid
};
#endif

#ifndef The_check_and_Element_Access_Members
template <typename T> 
void Blob<T>::check(size_type i, const string &msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

template <typename T> 
T &Blob<T>::back() {
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T> 
T &Blob<T>::operator[](size_type i) {
	check(i, "subscript out of range"); // if i is too big,	check will throw, preventing access to a nonexistent element
	return (*data)[i];
}
#endif

#ifndef Blob_Constructors
template <typename T> 
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template <typename T> 
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}
#endif

template <typename T> 
void Blob<T>::pop_back() { //MINE
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}