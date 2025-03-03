#if 0

#include "../../stdafx.h"
#include "3_15 Деструкторы и время жизни объекта.h"

void example_1() {
	for (int i : {0, 1}) { //TEST!
		cout << "Step " << i << ": 1\n";
		Route route;
		cout << "Step " << i << ": 2\n";
	}
	cout << "End\n";
}

#ifdef ORIG
// Why didn't the temporary Route object's destructor get called in GetRoute():
// 1) Because the Route default move constructor got called?
// 2) Because the compiler optimized the code?
// Answer:
// The temporary Route object's destructor did not get called in GetRoute() because of the compiler optimization known as Return Value Optimization (RVO). RVO is a compiler optimization technique where the compiler eliminates the unnecessary copy or move operations by constructing the return value directly in the memory location of the caller's context.
// In this case, when GetRoute() is called, the compiler optimizes the creation of the temporary Route object by constructing it directly in the memory location where the object will be used in the caller function.This optimization avoids the need for a temporary object to be created and then destroyed, resulting in improved performance by reducing unnecessary object copying.
Route GetRoute() {
#else //MINE
Route &&GetRoute() {
#endif
	cout << "1\n";
	return {};
}

void example_2() {
	Route route = GetRoute();
	cout << "2\n";
}

int main() {
	PRINT_FILE_LINE();
	//example_1();
	example_2();
}
#endif