#ifdef ON

#include <iostream>
#include <vector>
#include "../../stdafx.h"
#include "14_03_1_1.h"
#include "16_01_1.h"
using namespace std;

namespace Function_Templates {
	template <typename T>
	int compare(const T &v1, const T &v2) {
		if (v1 < v2)
			return -1;
		if (v2 < v1)
			return 1;
		return 0;
	}
}

void Instantiating_a_Function_Template() {
	cout << Function_Templates::compare(1, 0) << endl; //ORIG cout << compare(1, 0) << endl; // instantiates int compare(const int&, const int&) // T is int

	vector<int> vec1{1, 2, 3}, vec2{4, 5, 6}; // instantiates int compare(const vector<int>&, const vector<int>&)
	cout << Function_Templates::compare(vec1, vec2) << endl;  //ORIG cout << compare(vec1, vec2) << endl; // T is vector<int>
}

#ifndef Template_Type_Parameters
template <typename T> T foo(T *p) { // ok: same type used for the return type and parameter
	T tmp = *p; // tmp will have the type to which p points
	// ...
	return tmp;
}

//TEST! template <typename T, U> T calc(const T &, const U &); //																								error: must precede U with either typename or class
//ERR template <typename T, class U> calc(const T &, const U &);
template <typename T, class U> T calc(const T &, const U &); //TEST! //MINE //																					ok: no distinction between typename and class in a template parameter list
#endif

namespace Nontype_Template_Parameters {
	template <unsigned N, unsigned M>
	int compare(const char(&p1)[N], const char(&p2)[M]) { //TEST!!! //																							E.g.: int compare(const char (&p1)[3], const char (&p2)[4])
		return strcmp(p1, p2);
	}

}

void Nontype_Template_Parameters_() {
	cout << "Nontype_Template_Parameters::compare(\"hi\", \"mom\") = " << Nontype_Template_Parameters::compare("hi", "mom") << '\n'; //ORIG compare("hi", "mom")
}

#ifndef inline_and_constexpr_Function_Templates
template <typename T> 
inline T min(const T &, const T &); //TEST! //																													ok: inline specifier follows the template parameter list
//TEST inline template <typename T> T min(const T &, const T &); //																								error: incorrect placement of the inline specifier
#endif

void Compilation_Errors_Are_Mostly_Reported_during_Instantiation() {
	Sales_data data1, data2;
	//TEST cout << compare(data1, data2) << endl; //																												error: no	< on Sales_data
}

void mine() {
	char a[] = "one";
	char b[] = "two";
	cout << "compare(\"" << a << "\", \"" << b << "\") = " << Nontype_Template_Parameters::compare(a, b) << '\n';

	cout << "compare(2.2f, 3.3f) = " << compare(2.2f, 3.3f) << '\n';
}

int main(int argc, char argv[]) {
	print_file_line();

	//Instantiating_a_Function_Template();
	Nontype_Template_Parameters_();
	//mine();

	return 0;
}
#endif

#ifdef EX_16_04

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "../../stdafx.h"
#include "14_08_2_util.h"
using namespace std;

template <typename T, typename U> 
T my_find(const T &iter_beg, const T &iter_end, const U &val) {
	T iter = iter_beg;
	while (iter != iter_end) {
		if (*iter == val)
			return iter;
		++iter;
	}
	return iter;
}

template <typename T> 
void search(const T &range) {
	cout << "The initial values:\n";
	auto out = ostream_iterator<typename T::value_type>(cout, " ");
	copy(range.cbegin(), range.cend(), out);

	cout << "\n\nFind the first element: " << *range.begin() << '\n';
	auto res = my_find(range.begin(), range.end(), *range.begin());
	if (res != range.end())
		cout << "The first element found is " << *res << '\n';
	else
		cout << "No matching element found!" << '\n';
}

int main(int argc, char argv[]) {
	print_file_line();

	Rnd rnd;
	vector<int> v(10);
	generate(v.begin(), v.end(), rnd);
	search(v);

	cout << "\n\n";
	list<string> l = {"one", "two", "three", "four"};
	search(l);

	return 0;
}
#endif

#ifdef EX_16_06 // ch16/16.6.cpp @ https://github.com/jaege/Cpp-Primer-5th-Exercises/blob/master/ch16/16.6.cpp

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T, size_t N> 
T *begin_arr(T(&arr)[N]) {
	return arr;
}

template <typename T, size_t N> 
T *end_arr(T(&arr)[N]) { //TEST!
	return arr + N;
}

int main(int argc, char argv[]) {
	print_file_line();

	int arr[] = {1, 2, 3, 4, 5};
	for (auto it = begin_arr(arr); it != end_arr(arr); ++it)
		std::cout << *it << std::endl;

	return 0;
}
#endif

#ifdef EX_16_07

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T, size_t N> 
constexpr size_t my_size(T const (&arr)[N]) {
	return N;
}

int main(int argc, char argv[]) {
	print_file_line();

	int arr[] = {1, 2, 3, 4, 5};

	cout << "The array:\n";
	copy(cbegin(arr), cend(arr), ostream_iterator<int>(cout, " "));
	cout << "\nhas size " << my_size(arr) << ".\n";

	return 0;
}
#endif