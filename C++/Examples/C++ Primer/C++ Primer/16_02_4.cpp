#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "16_01_1.h"
using namespace std;

#pragma region Function Pointers and Argument Deduction
template <typename T>
int compare(const T &, const T &);

int (*pf1)(const int &, const int &) = compare; //TEST! //																												pf1 points to the instantiation int compare(const int&, const int&)

void func(int(*)(const string &, const string &)); //TEST //																											overloaded versions of func; each takes a different function pointer type
void func(int(*)(const int &, const int &));

void Function_Pointers_and_Argument_Deduction() {
	//TEST func(compare); // error: which instantiation of compare?
	//TEST! func(compare<int>); //																																		passing compare(const int&, const int&) // ok: explicitly specify which version of compare to instantiate
}
#pragma endregion

void mine() {
	cout << "compare<int>(1, 2) = " << compare<int>(1, 2) << '\n';
	auto n2 = compare(1, 2);
	auto n3 = compare(1.0, 2.0);

	cout << "pf1(1, 2) = " << pf1(1, 2) << '\n';
}

int main() {
	print_file_line();

	mine();
}
#endif
