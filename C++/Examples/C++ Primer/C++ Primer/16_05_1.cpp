#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Template Specializations
#ifdef ORIG
template <typename T>
int compare(const T &, const T &); // first version; can compare any two types

template <size_t N, size_t M>
int compare(const char(&)[N], const char(&)[M]); // second version to handle string literals

#else //MINE

#pragma region Function Templates
template <typename T>
int compare(const T &v1, const T &v2) {
	cout << "template <typename T>\nint compare(const T & v1, const T & v2)\n\n"; //MINE
	if (v1 < v2)
		return -1;
	if (v2 < v1)
		return 1;
	return 0;
}
#pragma endregion

#ifndef Defining_a_Function_Template_Specialization
template <> //TEST!!
int compare(const char *const &p1, const char *const &p2) { //TEST! //																					special version of compare to handle pointers to character arrays
	cout << "template <>\nint compare(const char *const &p1, const char *const &p2)\n\n";
	return strcmp(p1, p2);
}
#endif

#pragma region Nontype_Template_Parameters
template <unsigned N, unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M]) {
	cout << "template <unsigned N, unsigned M>\nint compare(const char(&p1)[N], const char(&p2)[M])\n\n";
	return strcmp(p1, p2);
}
#pragma endregion

void Template_Specializations() {
	const char *p1 = "hi", *p2 = "mom";
	compare(p1, p2); // calls the first template
	compare("hi", "mom"); // calls the template with two nontype parameters
}
#pragma endregion
#endif 

int main() {
	print_file_line();

	Template_Specializations();
}
#endif
