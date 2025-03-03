#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Template Argument Deduction and References
template <typename T> 
void f(T &p);
#pragma endregion

#pragma region Type Deduction from Lvalue Reference Function Parameters
template <typename T>
void f1(T &); // argument must be an lvalue

#pragma region MINE
template <typename T>
void f1(T &) {/**/} //MINE

int i{};
const int ci = i;
#pragma endregion

void Type_Deduction_from_Lvalue_Reference_Function_Parameters_1() { // calls to f1 use the referred-to type of the argument as the template parameter type
	f1(i); // i is an int; template parameter T is int
	f1(ci); // ci is a const int; template parameter T is const int
	//TEST! f1(5); //																																				error: argument to a & parameter must be an lvalue
}

template <typename T>
void f2(const T &); // can take an rvalue

template <typename T>
void f2(const T &) {/**/} //MINE

void Type_Deduction_from_Lvalue_Reference_Function_Parameters_2() { // parameter in f2 is const &; const in the argument is irrelevant // in each of these three calls, f2’s function parameter is inferred as const int&
	f2(i); // i is an int; template parameter T is int
	f2(ci); // ci is a const int, but template parameter T is int
	f2(5); //TEST //																																				a const & parameter can be bound to an rvalue; T is int
}
#pragma endregion

#pragma region Type Deduction from Rvalue Reference Function Parameters
template <typename T>
void f3(T &&);

void Type_Deduction_from_Rvalue_Reference_Function_Parameters() {
	f3(42); // argument is an rvalue of type int; template parameter T is int
}
#pragma endregion

void Reference_Collapsing_and_Rvalue_Reference_Parameters() {
	f3(i); // argument is an lvalue; template parameter T is int&
	f3(ci); // argument is an lvalue; template parameter T is const int&
}

#pragma region Writing Template Functions with Rvalue Reference Parameters
template <typename T> 
void f3(T &&val) {
	T t = val; //TEST! //																																		copy or binding a reference?
	//ERR t = fcn(t); //																																		does the assignment change only t or val and t?
	if (val == t) { /* ... */ } //TEST!	//																														always true if T is a reference type
}

void Writing_Template_Functions_with_Rvalue_Reference_Parameters() {
	f3(42);
	f3(i);
}
#pragma endregion

int main() {
	print_file_line();

	Writing_Template_Functions_with_Rvalue_Reference_Parameters();
}
#endif

#ifdef EX_16_42

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T> 
void g(T &&val) {
	;
}

int main() {
	print_file_line();

	int i = 0; 
	const int ci = i;

	g(i); //TEST! // (a) 
	g(ci); // (b)
	g(i * ci); // (c)
}
#endif

#ifdef EX_16_43

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T>
void g(T &&val) {
	;
}

int main() {
	print_file_line();

	int i = 0;
	const int ci = i;

	g(i = ci);
}
#endif

#ifdef EX_16_44

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T>
void g1(T val) {
	;
}

template <typename T>
void g2(const T &val) {
	;
}

int main() {
	print_file_line();

	int i = 0;
	const int ci = i;

	g1(i); // (a) 
	g1(ci); // (b)
	g1(i * ci); // (c)

	g2(i); // (a) 
	g2(ci); // (b)
	g2(i * ci); // (c)
}
#endif

#ifdef EX_16_45

#include <iostream>
#include <vector>
#include "../../stdafx.h"
using namespace std;

template <typename T> 
void g(T &&val) { 
	vector<T> v; 
}

int main() {
	print_file_line();

	//TEST! g(42);
	
	int i{};
	//TEST! g(i);
}
#endif