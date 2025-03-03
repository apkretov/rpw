#ifdef ON
#include <iostream>
#include <map>
#include <functional>
#include "../../stdafx.h"
using namespace std;

#ifndef Different_Types_Can_Have_the_Same_Call_Signature
int add(int i, int j) { // ordinary function
	return i + j; 
} 

auto mod = [](int i, int j) { return i % j; }; // lambda, which generates an unnamed function-object class

struct divide { // function-object class
	int operator()(int denominator, int divisor) {
	return denominator / divisor;
	}
};

void Different_Types_Can_Have_the_Same_Call_Signature_() {
	map<string, int(*)(int, int)> binops; // maps an operator to a pointer to a function taking two ints and returning an int
	
	// ok: add is a pointer to function of the appropriate type
	binops.insert({"+", add}); // {"+", add} is a pair § 11.2.3 (p. 426)
	binops.insert({"%", mod}); //TEST! //																																								error: mod is not a pointer to function
}
#endif

#define The_Library_function_Type
#ifdef The_Library_function_Type
void The_Library_function_Type_() {
	function<int(int, int)> f1 = add; // function pointer
	function<int(int, int)> f2 = divide(); //TEST! //																																					object of a function-object class
	function<int(int, int)> f3 = [](int i, int j) { return i * j; }; //TEST! //																															lambda
	cout << f1(4, 2) << endl; // prints 6
	cout << f2(4, 2) << endl; // prints 2
	cout << f3(4, 2) << endl; // prints 8

	map<string, function<int(int, int)>> binops = {
		{"+", add}, // function pointer
		{"-", std::minus<int>()}, // library function object
		{"/", divide()}, // user-defined function object
		{"*", [](int i, int j) { return i * j; }}, // unnamed lambda
		{"%", mod} // named lambda object
	}; 
	binops["+"](10, 5); // calls add(10, 5)
	binops["-"](10, 5); // uses the call operator of the minus<int> object
	binops["/"](10, 5); // uses the call operator of the divide object
	binops["*"](10, 5); // calls the lambda function object
	binops["%"](10, 5); // calls the lambda function object
}

#else
#include "14_03_1.h"
void Overloaded_Functions_and_function_() {
		int add(int i, int j); //ORIG { return i + j; }
		Sales_data add(const Sales_data &, const Sales_data &);
		map<string, function<int(int, int)>> binops;
		//TEST! binops.insert({"+", add}); //																																							error: which add?
		int (*fp)(int, int) = add; //TEST! //																																							pointer to the version of add that takes two ints
		binops.insert({"+", fp}); //TEST! //																																							ok: fp points to the right version of add

		binops.insert({"+", [](int a, int b) {return add(a, b); }}); //TEST! //																															ok: use a lambda to disambiguate which version of add we want to use
}
#endif

int main(int argc, char *argv[]) {
	print_file_line();
	
	//Different_Types_Can_Have_the_Same_Call_Signature_();
#ifdef The_Library_function_Type
	The_Library_function_Type_();
#else
	Overloaded_Functions_and_function_();
#endif

	return 0;
}
#endif
