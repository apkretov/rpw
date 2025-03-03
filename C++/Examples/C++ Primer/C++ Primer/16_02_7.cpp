#ifdef ON

#include <iostream>
#include <utility>
#include "../../stdafx.h"
using namespace std;

#pragma region Forwarding
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) { // template that takes a callable and two parameters // and calls the given callable with the parameters ‘‘flipped’’ // flip1 is an incomplete implementation: top-level const and references are lost
	f(t2, t1);
}

void f(int v1, int &v2) { // note v2 is a reference
	cout << v1 << " " << ++v2 << endl;
}

int i{}; //MINE
int j{}; //MINE

void Forwarding() {
	cout << "i = " << i << '\n'; //MINE
	f(42, i); // f changes its argument i
	cout << "i = " << i << '\n'; //MINE


	cout << '\n' << "j = " << j << '\n'; //MINE
	flip1(f, j, 42); // f called through flip1 leaves j unchanged
	cout << "j = " << j << '\n'; //MINE
}
#pragma endregion

#pragma region Defining Function Parameters That Retain Type Information
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2) {
	f(t2, t1);
}

void mine1() {
	cout << "j = " << j << '\n';
	flip2(f, j, 42);
	cout << "j = " << j << '\n';
}

#ifdef ORIG
void g(int &&i, int &j) {
	cout << i << " " << j << endl;
}
#else //MINE
void g(int &&v1, int &v2) {
	cout << v1 << " " << ++v2 << endl;
}
#endif

void Defining_Function_Parameters_That_Retain_Type_Information() {
	//TEST! flip2(g, i, 42); //																																		error: can’t initialize int&& from an lvalue
}
#pragma endregion

#pragma region Using std::forward to Preserve Type Information in a Call
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void Using_std_forward_to_Preserve_Type_Information_in_a_Call() {
	cout << "i = " << i << '\n'; //MINE
	flip(g, i, 42);
	cout << "i = " << i << '\n'; //MINE
}
#pragma endregion

int main() {
	print_file_line();

	//Forwarding();
	//mine1();
	//Using_std_forward_to_Preserve_Type_Information_in_a_Call();
	//Defining_Function_Parameters_That_Retain_Type_Information();
	Using_std_forward_to_Preserve_Type_Information_in_a_Call();
}
#endif
