#include "stdafx.h"

int min(int a, int b) { return a <= b ? a : b; }
int max(int a, int b) { return a >= b ? a : b; }

int compare1(int a, int b, int (*fncCompare1)(int, int)) { return fncCompare1(a, b); }
int compare2(int a, int b, int fncCompare2(int, int)) { return fncCompare2(a, b); };

void mine() {
	int a = 25, b = 30;
	printf("min of %i and %i is %i\n", a, b, compare1(a, b, min));
	printf("max of %i and %i is %i\n\n", a, b, compare2(a, b, max));
}

int add(int a, int b) {return a + b;}; //Function Pointers in C / C++ @ https://www.youtube.com/watch?v=ynYtgGUNelE
int (*mptrAdd)(int, int); //Module scope.

void functionPointersInCpp() {
	int (*ptrAdd)(int, int); //Local scope.
	ptrAdd = mptrAdd = add; //This version is more often used.
	printf("mptrAdd(2, 3) = %i\n", mptrAdd(2, 3));
	printf("ptrAdd(20, 30) = %i\n", ptrAdd(20, 30));
	ptrAdd = mptrAdd = &add; //This is equivalent.
	printf("mptrAdd(200, 300) = %i\n", mptrAdd(100, 200));
	printf("ptrAdd(2000, 3000) = %i\n\n", ptrAdd(2000, 3000));
}

int main() {
	mine();
	functionPointersInCpp();
	return 0;
}







































