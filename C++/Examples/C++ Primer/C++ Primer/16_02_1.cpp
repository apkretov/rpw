#ifdef ON

#include <iostream>
#include <fstream>
#include "../../stdafx.h"
#include "16_01_1.h"
using namespace std;

#pragma region Conversions and Template Type Parameters
template <typename T> T fobj(T, T) { return T(); } //ORIG template <typename T> T fobj(T, T); // arguments are copied
template <typename T> T fref(const T &, const T &) { return T(); } //ORIG template <typename T> T fref(const T &, const T &); // references

void Conversions_and_Template_Type_Parameters() {
	string s1("a value");
	const string s2("another value");
	fobj(s1, s2); //TEST! //																																		calls fobj(string, string); const is ignored
	fref(s1, s2); //TEST! //																																		calls fref(const string&, const string&) // calls fref(const string&, const string&)

	int a[10], b[42]; // uses premissible conversion to const on s1
	fobj(a, b); // calls f(int*, int*)
	//TEST! fref(a, b); // error: array types don’t match
}
#pragma endregion

#pragma region Function Parameters That Use the Same Template Parameter Type
template <typename A, typename B> // argument types can differ but must be compatible
int flexibleCompare(const A &v1, const B &v2) {
	if (v1 < v2)
		return -1;
	if (v2 < v1)
		return 1;
	return 0;
}

void Function_Parameters_That_Use_the_Same_Template_Parameter_Type() {
	long lng;
	//TEST! compare(lng, 1024); //																																	error: cannot instantiate compare(long, int)

	flexibleCompare(lng, 1024); // ok: calls flexibleCompare(long, int)
}
#pragma endregion

#pragma region Normal Conversions Apply for Ordinary Arguments
template <typename T>
ostream &print(ostream &os, const T &obj) {
	return os << obj;
}

void Normal_Conversions_Apply_for_Ordinary_Arguments() {
	print(cout, 42); // instantiates print(ostream&, int)
	ofstream f("output");
	//OFF print(f, 10); // uses print(ostream&, int); converts f to ostream&
}
#pragma endregion


int main() {
	print_file_line();
	//Conversions_and_Template_Type_Parameters();
	Normal_Conversions_Apply_for_Ordinary_Arguments();
}
#endif

#ifdef EX_16_34

#include <iostream>
#include "../../stdafx.h"
#include "16_01_1.h"
using namespace std;

template <class T>
int compare(const T &, const T &);

int my_compare(const char *arr1, const char *arr2) {
	if (less<const char *>()(arr1, arr2))
		return -1;
	if (less<const char *>()(arr2, arr1))
		return 1;
	return 0;
}

int main() {
	print_file_line();

	//TEST! compare("hi", "world"); // (a) 
	cout << R"(compare("bye", "dad") = )" << compare("bye", "dad") << '\n'; // (b) //TEST!
	cout << R"(compare("dad", "bye") = )" << compare("dad", "bye") << '\n'; //TEST! //MINE

	//MINE
	cout << '\n';
	cout << R"(compare(string("bye"), string("dad")) = )" << compare(string("bye"), string("dad")) << '\n';
	cout << R"(compare(string("dad"), string("bye")) = )" << compare(string("dad"), string("bye")) << '\n';
	cout << R"(compare(string("hi"), string("world")) = )" << compare(string("hi"), string("world")) << '\n';

	//MINE
	cout << '\n';
	cout << R"(my_compare("dad", "bye") = )" << my_compare("dad", "bye") << '\n';
	cout << R"(my_compare("bye", "dad") = )" << my_compare("bye", "dad") << '\n';
	cout << R"(my_compare("hi", "world") = )" << my_compare("hi", "world") << '\n';
}
#endif

#ifdef EX_16_35

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T>
T calc(T, int) {
	return T();
}

template <typename T>
T fcn(T, T) {
	return T();
}

int main() {
	print_file_line();

	double d{};
	float f{};
	char c{};

	calc(c, 'c'); // (a)
	calc(d, f); // (b)

	fcn(c, 'c'); // (c) //TEST!
	//TEST! fcn(d, f); // (d)
	//TEST! fcn(f, d); //MINE

}
#endif

#ifdef EX_16_36

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T> 
void f1(T, T) {/**/}

template <typename T1, typename T2>
void f2(T1, T2) {/**/}

int main() {
	print_file_line();

	int i = 0;
	int j = 42;

	int *p1 = &i;
	int *p2 = &j;

	const int *cp1 = &i;
	const int *cp2 = &j;

	f1(p1, p2); // (a)
	f2(p1, p2); // (b) //TEST!
	f1(cp1, cp2); // (c) 
	f2(cp1, cp2); // (d)
	//TEST! f1(p1, cp1); // (e) 
	f2(p1, cp1); // (f)
}
#endif