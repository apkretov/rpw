#ifdef ON

#include "../../stdafx.h"
#include "16_03_2.h"
using namespace std;

#pragma region Writing Overloaded Templates
string s("hi");

void Writing_Overloaded_Templates() {
	cout << debug_rep(s) << endl;
	cout << debug_rep(&s) << endl;
}
#pragma endregion

void Multiple_Viable_Templates() {
	const string *sp = &s;
	cout << debug_rep(sp) << endl;
}

void Nontemplate_and_Template_Overloads() {
	cout << debug_rep(s) << endl;
}

void Overloaded_Templates_and_Conversions() {
	cout << debug_rep("hi world!") << endl; // calls debug_rep(T*)
}

#ifdef Missing_Declarations_Can_Cause_the_Program_to_Misbehave
template <typename T>
string debug_rep(const T &t);

template <typename T>
string debug_rep(T *p);

string debug_rep(const string &); // the following declaration must be in scope // for the definition of debug_rep(char*) to do the right thing

string debug_rep(char *p) {
	return debug_rep(string(p)); // if the declaration for the version that takes a const string& is not in scope // the return will call debug_rep(const T&) with T instantiated to string
}
#endif

int main() {
	print_file_line();

	//Writing_Overloaded_Templates();
	//Multiple_Viable_Templates();
	//Nontemplate_and_Template_Overloads();
	Overloaded_Templates_and_Conversions();
}
#endif

#ifdef EX_16_49

#include <iostream>
#include "../../stdafx.h"
using namespace std;

template <typename T> 
void f(T) {
	;
}

template <typename T> 
void f(const T *) {
	;
}

template <typename T> 
void g(T) {
	;
}

template <typename T> 
void g(T *) {
	;
}

int main() {
	print_file_line();

	int i = 42, *p = &i;
	const int ci = 0, *p2 = &ci;

	g(42); 
	g(p); 
	g(ci); 
	g(p2);
	
	f(42); 
	f(p); 
	f(ci); 
	f(p2);
}
#endif
