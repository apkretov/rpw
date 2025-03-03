#ifdef	ON

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "14_03_1_1.h"
using std::cout;
using std::cin;
using std::less;
using std::vector;

#ifndef TemplateParameters
//ORIG template <typename Foo> Foo calc(const Foo &a, const Foo &b) {
template <typename Foo> Foo calc(const Foo &a, [[maybe_unused]] const Foo &b) { //TEST! //MINE
	Foo tmp = a; // tmp has the same type as the parameters and return type
	// ...
	return tmp; // return type and parameters have the same type
}
#endif

#ifndef Template_Parameters_and_Scope
//ORIG typedef double A;
using A = double; //MINE
//ORIG template <typename A, typename B> void f(A a, B b) {
template <typename A, typename B> void f(A a, [[maybe_unused]] B b) { //MINE
	A tmp = a; //TEST! //																																		tmp has same type as the template parameter A, not double
	//TEST! double B; //																																		error: redeclares template parameter B
}

//TEST! template <typename V, typename V> // ... //																												error: illegal reuse of template parameter name V
#endif

#ifdef Template_Declarations
template <typename T> int compare(const T &, const T &); // declares but does not define compare and Blob
template <typename T> class Blob;

template <typename T> T calc(const T &, const T &); //TEST!	// 																									declaration // all three uses of calc refer to the same function template
template <typename U> U calc(const U &, const U &); //TEST! //																									declaration
template <typename Type> Type calc(const Type &a, const Type &b) { /* ... */ } //TEST! //																		definition of the template
#endif

#ifndef Using_Class_Members_That_Are_Types
//TEST! T::size_type *p; //																																		it needs to know whether we’re defining a variable named p or are multiplying a static data member named size_type by a variable named p
template <typename T> 
typename T::value_type top(const T &c) { //TEST! //																											We do so by using the keyword typename
	if (!c.empty())
		return c.back();
	else
		return typename T::value_type();
}
#endif

#ifndef Default_Template_Arguments
template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, F f = F()) { //TEST! //																									compare has a default template argument, less<T> and a default function argument, F()
	if (f(v1, v2))
		return -1;
	if (f(v2, v1))
		return 1;
	return 0;
}

bool compareIsbn(const Sales_data & lhs, const Sales_data & rhs); // Forward declaration. //MINE 

void Default_Template_Arguments_() {
	bool i = compare(0, 42); // uses less; i is -1
	cout << "compare(0, 42) = " << i << '\n'; //MINE
	
	cout << "\nEnter Sales_data item1 & item2:\n"; //MINE
	Sales_data item1(cin), item2(cin); // result depends on the isbns in item1 and item2
	bool j = compare(item1, item2, compareIsbn);
	cout << "compare(item1, item2, compareIsbn) = " << j << '\n'; //MINE
}
#endif

#ifndef Template_Default_Arguments_and_Class_Templates
template <class T = int> class Numbers { //TEST! //																												by default T is int
public:
	Numbers(T v = 0) : val(v) {}
	// various operations on numbers
private:
	T val;
};

void Template_Default_Arguments_and_Class_Templates_() {
	Numbers<long double> lots_of_precision;
	Numbers<> average_precision; //TEST! //																														uses default type int // empty <> says we want the default type
}
#endif

template <class T = int>
void mine() {
	vector<T> v = {1, 2, 3};
	cout << "top1(v) = " << top(v) << '\n';
	v.clear();
	cout << "top1(v) = " << top(v) << '\n';
}

int main(int argc, char *argv[]) {
	print_file_line();

	Default_Template_Arguments_();
	//mine(); //TEST! //																																			The same as mine<>();

	return 0;
}
#endif

#ifdef EX_16_17

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using std::cout;
using std::vector;

template <typename T>
typename T::value_type top1(const T &c) {
	if (!c.empty())
		return c.back();
	else
		return typename T::value_type();
}

template <class T>
class T::value_type top2(const T &c) {
	if (!c.empty())
		return c.back();
	else
		return typename T::value_type(); //TEST! //																											typename but not class here!
}

template <class T = int>
void mine() {
	vector<T> v = {1, 2, 3};
	cout << "top1(v) = " << top(v) << '\n';
	v.clear();
	cout << "top1(v) = " << top(v) << '\n';
}

int main(int argc, char *argv[]) {
	print_file_line();

	vector<int> v;
	cout << "top1(v) = " << top1(v) << '\n';
	//TEST! cout << "top2(v) = " << top2(v) << '\n';

	return 0;
}
#endif

#ifdef EX_16_18

#include <iostream>
#include "../../stdafx.h"
using std::cout;

//TEST template <typename T, U, typename V> void f1(T, U, V); // (a)

//OFF template <typename T> T f2(int &T); // (b)

//TEST! inline template <typename T> T foo(T, unsigned int *); // (c)

//TEST template <typename T> f4(T, T); // (d)

typedef char Ctype; // (e) //TEST
template <typename Ctype> Ctype f5(Ctype a);

int main(int argc, char *argv[]) {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_16_19

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include "../../stdafx.h"
using std::cout;
using std::vector;
using std::deque;
using std::string;

//you.com
//if we were to use std::size(v) instead of std::ssize(v) in the loop condition, we would encounter an issue.The problem arises because std::size returns an unsigned type(std::size_t), and when we subtract 1 from 0, it would result in an underflow, leading to an infinite loop.
//By using std::ssize, which returns a signed type(std::ptrdiff_t), we can safely perform the loop and iterate over the elements in reverse order without worrying about unsigned underflow.
void use_ssize_vs_size() {
	vector<int> v = {1, 2, 3, 4, 5};

	for (auto i = ssize(v) - 1; i >= 0; --i) //TEST!
		//ERR for (auto i = size(v) - 1; i >= 0; --i)
		cout << v[i] << ' ';
}

template <typename T>
void print_vector(const vector<T> &v) {
	for (typename vector<T>::size_type i = 0; i != size(v); ++i)
		cout << v.at(i) << ' ';
}

template <typename contr>
void print_container(const contr &c) {
	for (typename contr::size_type i = 0; i != ssize(c); ++i)
		cout << c.at(i) << ' ';
}

int main(int argc, char *argv[]) {
	print_file_line();

	vector<int> v = {1, 2, 3};
	print_vector(v);
	cout << '\n';

	print_container(v);
	cout << '\n';

	deque<string> dq = {"ss", "sszz", "saaas", "s333s", "ss2"," sss"};
	print_container(dq);
	cout << '\n';

	return 0;
}
#endif

#ifdef EX_16_20

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include "../../stdafx.h"
using std::cout;
using std::vector;
using std::deque;
using std::string;


template <typename T>
void print_vector(const vector<T> &v) {
	for (auto it = cbegin(v); it != cend(v); ++it)
		cout << *it << ' ';
}

template <typename contr>
void print_container(const contr &c) {
	for (auto it = cbegin(c); it != cend(c); ++it)
		cout << *it << ' ';
}

int main(int argc, char *argv[]) {
	print_file_line();

	vector<int> v = {1, 2, 3};
	print_vector(v);
	cout << '\n';

	print_container(v);
	cout << '\n';

	deque<string> dq = {"ss", "sszz", "saaas", "s333s", "ss2"," sss"};
	print_container(dq);
	cout << '\n';

	return 0;
}
#endif
