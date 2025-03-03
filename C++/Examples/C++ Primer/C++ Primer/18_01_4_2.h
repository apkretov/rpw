#pragma once

#include <initializer_list>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>
#include "../../stdafx.h"
using std::cerr;
using std::bad_alloc;
using std::initializer_list;
using std::make_shared;
using std::ostream;
using std::ostream_iterator;
using std::out_of_range;
using std::ranges::copy;
using std::shared_ptr;
using std::string;
using std::vector;

#ifndef One_to_One_Friendship
#ifdef ORIG
template <typename> class BlobPtr; // forward declarations needed for friend declarations in Blob
template <typename> class Blob; // needed for parameters in operator==
#else MINE
template <typename T> class BlobPtr; // forward declarations needed for friend declarations in Blob
template <typename T> class Blob; // needed for parameters in operator==
#endif
template <typename T> bool operator==(const Blob<T> &, const Blob<T> &);
#endif

#ifndef Defining_a_Class_Template
template <typename T>
class Blob { //VER6
#ifndef One_to_One_Friendship // each instantiation of Blob grants access to the version of BlobPtr and the equality operator instantiated with the same type
	friend class BlobPtr<T>;
	friend bool operator==<T>(const Blob<T> &, const Blob<T> &);
	friend ostream &operator<<<T>(ostream &, const Blob<T> &); //MINE
#endif // other members as in § 12.1.1 (p. 456)
public:
	using value_type = T; //OIRG typedef T value_type;
	using size_type = typename vector<T>::size_type; //ORIG typedef typename vector<T>::size_type size_type;
#pragma region EX_18_08
	Blob() noexcept(false); // constructors
	explicit Blob(initializer_list<T> il) noexcept(false); //MINE //ORIG Blob(initializer_list<T> il);
#pragma endregion
#pragma region Member_Templates_of_Class_Templates
#pragma region EX_18_08
	template <typename It>
	Blob(It b, It e) noexcept(false);
#pragma endregion
#pragma endregion
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
#pragma region Function try Blocks and Constructors
void handle_out_of_memory(const bad_alloc &e) { //MINE
	cerr << log_str(e.what()) << '\n';
}

template <typename T>
#pragma region EX_18_08
Blob<T>::Blob(initializer_list<T> il) noexcept(false) try : data(make_shared<vector<T>>(il)) {
#pragma endregion
	/* empty body */
}
catch (const bad_alloc &e) {
	handle_out_of_memory(e);
}
#pragma endregion

#pragma region EX_18_07
template <typename T>
#pragma region EX_18_08
Blob<T>::Blob() noexcept(false) try : data(make_shared<vector<T>>()) {/*empty*/ }
#pragma endregion
catch (const bad_alloc &e) {
	handle_out_of_memory(e);
}
#pragma endregion
#endif

#pragma region Member_Templates_of_Class_Templates
template <typename T> // type parameter for the class
template <typename It> // type parameter for the constructor
#pragma region EX_18_07
#pragma region EX_18_08
Blob<T>::Blob(It b, It e) noexcept(false) try : data(make_shared<vector<T>>(b, e)) {/*empty*/ }
#pragma endregion
catch (const bad_alloc &e) {
	handle_out_of_memory(e);
}
#pragma endregion
#pragma endregion

template <typename T>
void Blob<T>::pop_back() { //MINE
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

template <typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) { //MINE
	return *lhs.data == *rhs.data;
}

template <typename T>
ostream &operator<<(ostream &out, const Blob<T> &b) { //MINE
	copy(*b.data, ostream_iterator<T>(out, " "));
	return out;
}
