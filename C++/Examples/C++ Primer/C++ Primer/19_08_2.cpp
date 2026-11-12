#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

void volatile_Qualifier() {
#pragma region MINE
	struct Task {};
	constexpr size_t max_size = 10;
	struct Screen {};
#pragma endregion

	volatile int display_register; //TEST! //																												int value that might change
	volatile Task *curr_task; // curr_task points to a volatile object
	volatile int iax[max_size]; // each element in iax is volatile
	volatile Screen bitmapBuf; // each member of bitmapBuf is volatile

	volatile int v; // v is a volatile int
	int *volatile vip; // vip is a volatile pointer to int
	volatile int *ivp; // ivp is a pointer to volatile int
	volatile int *volatile vivp; //TEST //																													vivp is a volatile pointer to volatile int
	//TEST int *ip = &v; //																																	error: must use a pointer to volatile
	//ERR *ivp = &v; // ok: ivp is a pointer to volatile
	vivp = &v; // ok: vivp is a volatile pointer to volatile
}

#pragma region Synthesized Copy Does Not Apply to volatile Objects
class Foo {
public:
	Foo(const volatile Foo &); //TEST! //																													copy from a volatile object
	Foo &operator=(volatile const Foo &); //TEST! //																										assign from a volatile object to a nonvolatile object
	Foo &operator=(volatile const Foo &) volatile; //TEST! //																								assign from a volatile object to a volatile object
	// remainder of class Foo
};
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif