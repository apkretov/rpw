#pragma once

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::initializer_list;

#ifndef One_to_One_Friendship
/* you.com:
In the context of C++ template declarations, both versions of the template declaration for the Blob class are syntactically correct, but they serve different purposes :
template <typename> class Blob; (Version 1) is a forward declaration of a class template without specifying the template parameter's name. This is a less common form but can be used when the name of the template parameter is not needed in a particular context, such as a forward declaration 
template <typename T> class Blob; (Version 2) is a more conventional forward declaration of a class template where T is the name given to the template parameter.This form is typically used when you need to refer to the template parameter within the declaration, such as when declaring friend functions or methods that use the template parameter
Given that the Blob class template in the provided code snippet uses T as the template parameter within its definition(e.g., typedef T value_type;), Version 2 is the correct form to use in this case.This is because the template parameter name T is required to define the member types and functions within the class template.Additionally, the most recent sources from MDN and Oracle's Programmer's Guide also use Version 2
*/
#ifdef ORIG
template <typename> class BlobPtr; //TEST! //																												forward declarations needed for friend declarations in Blob
template <typename> class Blob; //TEST! //																													needed for parameters in operator==
#else MINE
template <typename T> class BlobPtr; //TEST! //																												forward declarations needed for friend declarations in Blob
template <typename T> class Blob; //TEST! //																												needed for parameters in operator==
#endif
template <typename T> bool operator==(const Blob<T> &, const Blob<T> &); //TEST!
#endif

#ifndef Defining_a_Class_Template
template <typename T> 
class Blob { //VER2
#ifndef One_to_One_Friendship // each instantiation of Blob grants access to the version of BlobPtr and the equality operator instantiated with the same type
	friend class BlobPtr<T>; 
	friend bool operator==<T>(const Blob<T> &, const Blob<T> &); //TEST!
#endif // other members as in � 12.1.1 (p. 456)
public:
	using value_type = T; //OIRG typedef T value_type;
	using size_type = typename vector<T>::size_type; //ORIG typedef typename vector<T>::size_type size_type;
	Blob(); // constructors
	Blob(initializer_list<T> il);

	size_type size() const { // number of elements in the Blob
		return data->size();
	}

	bool empty() const {
		return data->empty();
	}

	void push_back(const T &t) { // add and remove elements
		data->push_back(t);
	}

	void push_back(T &&t) { // move version; see � 13.6.3 (p. 548)
		data->push_back(std::move(t));
	}

	void pop_back();
	T &back(); // element access
	T &operator[](size_type i); // defined in � 14.5 (p. 566)
private:
	shared_ptr<vector<T>> data;
	void check(size_type i, const string &msg) const; // throws msg if	data[i] isn�t valid
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

template <typename T> 
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) { //TEST! //MINE
	return *lhs.data == *rhs.data;
}