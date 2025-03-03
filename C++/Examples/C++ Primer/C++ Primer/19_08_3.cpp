#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Declaring a Non-C++ Function
extern "C" size_t strlen(const char *); // illustrative linkage directives that might appear in the C++ header <cstring> // single-statement linkage directive

extern "C" { //TEST! //																																	compound-statement linkage directive
	int strcmp(const char *, const char *);
	char *strcat(char *, const char *);
}
#pragma endregion

#pragma region Linkage Directives and Headers
extern "C" { // compound-statement linkage directive
#include <string.h> //TEST! //																															C functions that manipulate C-style strings
}
#pragma region

#pragma region Pointers to extern "C" Functions
extern "C" void (*pf)(int); //TEST //																													pf points to a C function that returns void and takes an int

void (*pf1)(int); // points to a C++ function
extern "C" void (*pf2)(int); // points to a C function

void Pointers_to_extern_C_Functions() {
	//TEST pf1 = pf2; //																																error: pf1 and pf2 have different types
}
#pragma endregion

#pragma region Linkage Directives Apply to the Entire Declaration
extern "C" void f1(void(*)(int)); //TEST! //																											f1 is a C function; its parameter is a pointer to a C function

extern "C" typedef void FC(int); //TEST! //																												FC is a pointer to a C function
void f2(FC *); //TEST! //																																f2 is a C++ function with a parameter that is a pointer to a C function
#pragma region

#pragma region Exporting Our C++ Functions to Other Languages
extern "C" double calc(double dparm) { //TEST //																										the calc function can be called from C programs
	/* ... */ 
	return 0; //MINE
} 
#pragma endregion

#pragma region PREPROCESSOR SUPPORT FOR LINKING TO C
#ifdef __cplusplus
extern "C" // ok: we’re compiling C++
#endif
int strcmp(const char *, const char *);
#pragma endregion

#pragma region Overloaded Functions and Linkage Directives
extern "C" void print(const char *); // error: two extern "C" functions with the same name
//TEST! extern "C" void print(int);

class SmallInt { /* ... */ };
class BigNum { /* ... */ };
extern "C" double calc(double); // the C function can be called from C and C++ programs // the C++ functions overload that function and are callable from C++
extern SmallInt calc(const SmallInt &); //TEST!
extern BigNum calc(const BigNum &);
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif