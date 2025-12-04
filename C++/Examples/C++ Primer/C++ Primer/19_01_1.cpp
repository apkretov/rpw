#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

void Overloading_new_and_delete() { // new expressions
	cout << R"(string *sp = new string("a value"):)" << '\n'; //MINE
	string *sp = new string("a value"); // allocate and initialize a string
	cout << "\nstring *arr = new string[10]:\n"; //MINE
	string *arr = new string[10]; // allocate ten default initialized strings

	cout << "\ndelete sp:\n"; //MINE
	delete sp; // destroy *sp and free the memory to which sp points
	cout << "\ndelete[] arr:\n"; //MINE
	delete[] arr; // destroy the elements in the array and free the memory
}

void The_operator_new_and_operator_delete_Interface() {
	void *operator new(size_t); // these versions might throw an exception // allocate an object
	void *operator new[](size_t); // allocate an array
	void operator delete(void *) noexcept; //ORIG void *operator delete(void *) noexcept; // free an object
	void operator delete[](void *) noexcept; //ORIG void *operator delete[](void *) noexcept; // free an array

	void *operator new(size_t, nothrow_t &) noexcept; //TEST! //																						versions that promise not to throw; see § 12.1.2 (p. 460)
	void *operator new[](size_t, nothrow_t &) noexcept;
	void operator delete(void *, nothrow_t &) noexcept; //ORIG void *operator delete(void *, nothrow_t &) noexcept;
	void operator delete[](void *, nothrow_t &) noexcept; //ORIG void *operator delete[](void *, nothrow_t &) noexcept;

	//TEST void *operator new(size_t, void *); //																										this version may not be redefined
}

#pragma region The malloc and free Functions
void *operator new(size_t size) {
	printf("void *operator new(size_t size): "); //MINE
	if (void *mem = malloc(size)) {
		printf("mem = %p\t size = %zu\n", mem, size); //MINE
		return mem;
	} else
		throw bad_alloc();
}
void operator delete(void *mem) noexcept { 
	printf("void operator delete(void *mem): mem = %p\n", mem); //MINE
	free(mem); 
}
#pragma endregion

int main() {
	print_file_line();

	//Overloading_new_and_delete();

	auto p = new int(1);
	delete p;

	return 0;
}
#endif
