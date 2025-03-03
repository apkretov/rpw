#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Variadic Templates
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest) // Args is a template parameter pack; rest is a function parameter pack // Args represents zero or more template type parameters // rest represents zero or more function parameters
//ORIG ; 
{ cout << t << '\n'; } //MINE

void Variadic_Templates() {
	int i = 0; 
	double d = 3.14; 
	string s = "how now brown cow";

#ifndef OFF
	foo(i, s, 42, d); // three parameters in the pack
	foo(s, 42, "hi"); // two parameters in the pack
	foo(d, s); // one parameter in the pack
	foo("hi"); // empty pack
#endif
}
#pragma endregion

#pragma region The sizeof... Operator
template <typename ... Args> 
void g(Args ... args) {
	cout << sizeof...(Args) << endl; //TEST! //																												number of type parameters
	cout << sizeof...(args) << endl; //TEST! //																												number of function parameters
}
#pragma endregion

int main() {
	print_file_line();

	Variadic_Templates();
	//g(1, 2, 3, 4, 5); //MINE
}
#endif
