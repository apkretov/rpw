#ifdef ON

#include <iostream>
#include <unordered_set>
#include "../../stdafx.h"
#include "16_05_1.h"
using namespace std;

#pragma region Function Templates
template <typename T>
int compare(const T &v1, const T &v2) {
	if (v1 < v2)
		return -1;
	if (v2 < v1)
		return 1;
	return 0;
}
#pragma endregion

#pragma region Defining a Function Template Specialization
template <>
int compare(const char *const &p1, const char *const &p2) { //TEST! //																							special version of compare to handle pointers to character arrays
	return strcmp(p1, p2);
}
#pragma endregion

#pragma region Nontype_Template_Parameters
template <unsigned N, unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M]) {
	return strcmp(p1, p2);
}
#pragma endregion

#pragma region Template Specializations
void Template_Specializations() {
	const char *p1 = "hi", *p2 = "mom";

	cout << "compare(p1, p2) = " << //MINE
		compare(p1, p2) // calls the first template
		<< '\n'; //MINE

	cout << R"(compare("hi", "mom") = )" << //MINE
		compare("hi", "mom") // calls the template with two nontype parameters
		<< '\n'; //MINE

	cout << R"(compare(string("hi"), string("mom")) = )" << compare(string("hi"), string("mom")) << '\n'; //MINE
}
#pragma endregion

void Class_Template_Specializations() {
	unordered_multiset<Sales_data> SDset; // uses hash<Sales_data> and Sales_data operator== from § 14.3.1 (p. 561)

	//MINE
	SDset.emplace("978-0-13-149505-1", 1, 1);
	SDset.emplace("978-0-13-149505-2", 2, 2);
	SDset.emplace("978-0-13-149505-3", 3, 3);
	ranges::copy(SDset, ostream_iterator<Sales_data>(cout, "\n"));
}

#ifdef Class_Template_Partial_Specializations
template <class T> // original, most general template
struct remove_reference {
	typedef T type;
};

template <class T> // partial specializations that will be used for lvalue and rvalue references
struct remove_reference<T &> { //TEST //																																lvalue references
	typedef T type;
};

template <class T>
struct remove_reference<T &&> { //TEST //																																rvalue references
	typedef T type;
};
#endif

void Class_Template_Partial_Specializations() {
	int i;
	remove_reference<decltype(42)>::type a; // decltype(42) is int, uses the original template
	remove_reference<decltype(i)>::type b; // decltype(i) is int&, uses first (T&) partial specialization
	remove_reference<decltype(std::move(i))>::type c; // decltype(std::move(i)) is int&&, uses second (i.e., T&&) partial specialization
}

#pragma region Specializing Members but Not the Class
template <typename T>
struct Foo {
	Foo(const T &t = T()) : mem(t) {}

	void Bar() { /* ... */
		cout << "Foo::Bar()\n"; //MINE
	}

	T mem;
	// other members of Foo
};

template <> // we’re specializing a template
void Foo<int>::Bar() { //TEST! //																																		we’re specializing the Bar member of Foo<int>
	// do whatever specialized processing that applies to ints
	cout << "Foo<int>::Bar()\n"; //MINE
}

void Specializing_Members_But_Not_The_Class() {
	Foo<string> fs; // instantiates Foo<string>::Foo()
	fs.Bar(); // instantiates Foo<string>::Bar()

	Foo<int> fi; // instantiates Foo<int>::Foo()
	fi.Bar(); // uses our specialization of Foo<int>::Bar()
}
#pragma endregion

int main() {
	print_file_line();

	//Template_Specializations();
	//Class_Template_Specializations();
	Specializing_Members_But_Not_The_Class();
}
#endif

#ifdef EX_16_63

#include <iostream>
#include "../../stdafx.h"
#include "16_05_2.h"
using namespace std;

int main() {
	print_file_line();

	vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<double> vd = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
	vector<string> vs = {"hi", "mom", "hi", "hi", "hi"};

	cout << "vi: ";
	ranges::copy(vi, ostream_iterator<int>(cout, " ")); 
	cout << "\nvd: ";
	ranges::copy(vd, ostream_iterator<double>(cout, " "));
	cout << "\nvs: ";
	ranges::copy(vs, ostream_iterator<string>(cout, " "));

	cout << "\n\ncount(vi, 3) = " << count(vi, 3);
	cout << "\ncount(vd, 5.5) = " << count(vd, 5.5);
	cout << '\n' << R"(count(vs, string("hi") = )" << count(vs, string("hi"));
	cout << '\n' << R"(count(vs, "hi") = )" << count(vs, "hi") << '\n';
}
#endif

#ifdef EX_16_64

#include <iostream>
#include "../../stdafx.h"
#include "16_05_2.h"
using namespace std;

int main() {
	print_file_line();

	vector<const char *> vc = {"hi", "mom", "hi", "hi", "hi"};

	cout << "vc: ";
	ranges::copy(vc, ostream_iterator<const char *>(cout, " "));

	cout << "\n\n" << R"(count(vc, "hi") = )" << count(vc, "hi") << '\n';
}
#endif

#ifdef EX_16_65

#include <iostream>
#include "../../stdafx.h"
#include "16_03_1.h"
using namespace std;

//#pragma region Nontemplate and Template Overloads
//string debug_rep(const string &s) { // print strings inside double quotes
//	return '"' + s + '"';
//}
//#pragma endregion

//#pragma region Overloaded Templates and Conversions
//string debug_rep(char *p) { // convert the character pointers to string and call the string version of debug_rep
//	return debug_rep(string(p));
//}
//
//string debug_rep(const char *p) {
//	return debug_rep(string(p));
//}
//#pragma endregion

template <>
string debug_rep(const char *p) {
	return debug_rep(string(p));
}

template <>
string debug_rep(char *p) {
	return debug_rep(string(p));
}

void Overloaded_Templates_and_Conversions() {
	cout << debug_rep("hi world!") << endl; // calls debug_rep(T*)
}

int main() {
	print_file_line();

	Overloaded_Templates_and_Conversions();
}
#endif