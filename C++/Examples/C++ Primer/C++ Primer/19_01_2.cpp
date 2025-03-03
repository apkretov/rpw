#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#ifdef Placement_new_Expressions
	new (place_address) type
	new (place_address) type(initializers)
	new (place_address) type[size]
	new (place_address) type[size]{braced initializer list}
#endif

void Explicit_Destructor_Invocation() {
	string *sp = new string("a value"); // allocate and initialize a string
	sp->~string(); //TEST!
}

void Perplexity() { // Like calling destroy, calling a destructor cleans up the given object but does not free the space in which that object resides. // Memory allocated using `new` must be explicitly deallocated using `delete`.
	struct MyClass {};
	auto *obj = new MyClass; // 1. Allocate Memory for the object.
	obj->~MyClass(); //TEST! //																																2. When you are done with the object and want to clean it up, you call the destructor explicitly.
	delete obj; //TEST! //																																	3. After calling the destructor, you need to deallocate the memory used by the object.
}

int main() {
	print_file_line();

	Explicit_Destructor_Invocation();

	return 0;
}
#endif
