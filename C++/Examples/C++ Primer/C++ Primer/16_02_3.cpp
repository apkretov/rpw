#ifdef ON

#include <algorithm>
#include <iostream>
#include <type_traits>
#include "../../stdafx.h"
#include "16_01_4_1.h"
using namespace std;

#pragma region Trailing Return Types and Type Transformation

template <typename It>
auto fcn(It beg, It end) -> decltype(*beg) { //TEST //																															a trailing return lets us declare the return type after the parameter list is seen
	// process the range

	//MINE
	std::copy(beg, end, ostream_iterator<decltype(*beg)>(cout, " ")); 
	cout << '\n';

	return *beg; // return a reference to an element from the range
}

void Trailing_Return_Types_and_Type_Transformation() {
	vector<int> vi = {1,2,3,4,5};
	Blob<string> ca = {"hi", "bye"};
	auto &i = fcn(vi.begin(), vi.end()); // fcn should return int&
	auto j = fcn(vi.begin(), vi.end()); //MINE
	//OFF auto &s = fcn(ca.begin(), ca.end()); // fcn should return string&
}
#pragma endregion

#pragma region The Type Transformation Library Template Classes
template <typename It>
//ORIG auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type { //TEST! //																				must use typename to use a type member of a template parameter; see § 16.1.3 (p. 670)
//MINE auto fcn2(It beg, It end) -> remove_reference<decltype(*beg)>::type { 
//MINE fcn2(It beg, It end) -> typename remove_reference_t<decltype(*beg)> { C++14
auto fcn2(It beg, It end) -> remove_reference_t<decltype(*beg)> { //TEST! //MINE //																								you.com: The use of typename is not necessary.
	// process the range
	return *beg; // return a copy of an element from the range
}
#pragma endregion

void mine() {
	vector<int> vi = {1,2,3,4,5};
	auto i = fcn2(vi.begin(), vi.end());
	cout << "i = " << i << '\n';
}

template <typename T>
remove_reference_t<T> &&move(T &&t) noexcept { //TEST!! //MINE // Back to Basics: Move Semantics (part 1 of 2) - Klaus Iglberger - CppCon 2019 - YouTube @ https://youtu.be/St0MNEU5b0o?si=sMkhtftcXrLl4C6i&t=917
	return static_cast<remove_reference_t<T> &&>(t);
}

void add_const_() { //MINE // you.com: std::add_const adds the const qualifier to the given type, except when the type is already const or a reference type.
	using A = add_const_t<int>; //TEST! // const int //																												is_const<A>::value = is_const_v<A>
	using B = add_const_t<const int>; // const int (unchanged)
	using C = add_const_t<const int *>; //TEST! //																													const int* const
	using D = add_const_t<int *const>; // int* const (unchanged)
	using E = add_const_t<const int &>; //TEST! //																													const int& (unchanged)

	cout << boolalpha;
	cout << "checking constness:" << '\n';
	cout << "A: " << is_const_v<A> << '\n'; // TEST! //																												is_const<A>::value = is_const_v<A>
	cout << "B: " << is_const_v<B> << '\n';
	cout << "C: " << is_const_v<C> << '\n';
	cout << "D: " << is_const_v<D> << '\n';
	cout << "E: " << is_const_v<E> << '\n';
}

void remove_extent_() { //MINE // you.com: std::remove_extent type trait is used to remove the extent (size) of an array type, leaving behind the element type.
	using A = remove_extent_t<int[5]>; //TEST! //																													int
	using B = remove_extent_t<int[][3]>; //TEST! //																													int[3]
	using C = remove_extent_t<int>; // int (unchanged)

	cout << "A: " << typeid(A).name() << '\n';
	cout << "B: " << typeid(B).name() << '\n';
	cout << "C: " << typeid(C).name() << '\n';
}

void remove_all_extents_() { //MINE // you.com: std::remove_all_extents type trait is used to remove all extents (sizes) of a multidimensional array type, leaving behind the element type.
	using A = remove_all_extents_t<int[5]>; // int
	using B = remove_all_extents_t<int[][3]>; //TEST! //																											int
	using C = remove_all_extents_t<int>; // int (unchanged)

	cout << "A: " << typeid(A).name() << '\n';
	cout << "B: " << typeid(B).name() << '\n';
	cout << "C: " << typeid(C).name() << '\n';
}


int main() {
	print_file_line();

	//Trailing_Return_Types_and_Type_Transformation();
	//mine();
	//add_const_();
	//remove_extent_();
	remove_all_extents_();
}
#endif

#ifdef EX_16_40 // ch16/ex16.40/main.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch16/ex16.40/main.cpp 

#include <iostream> 
#include <vector>
#include "../../stdafx.h"
using namespace std;

template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0) {
	// process the range
	return *beg; // return a copy of an element from the range
}

class Bar {}; // As shown below, only type that support this + 0 operation can be passed. The return type depends on the what type the operator + returns. In the case below, the return type is Bar.

Bar operator +(Bar lhs, int) {
	return lhs;
}

int main() {
	print_file_line();

	vector<Bar> v;
	v.push_back(Bar());
	Bar b = fcn3(v.begin(), v.end());
}
#endif

#ifdef EX_16_41 // ch16/ex16.41/main.cpp @ https://github.com/Mooophy/Cpp-Primer/blob/master/ch16/ex16.41/main.cpp

#include <iostream> 
#include "../../stdafx.h"
using namespace std;

template <typename T>
auto sum(T lhs, T rhs) -> decltype(lhs + rhs) { //TEST!
	return lhs + rhs;
}

int main() {
	print_file_line();

	auto s = sum(12345678912345678912, 12345678912345678912);
	cout << "sum(12345678912345678912, 12345678912345678912) = " << s << '\n';
}
#endif