#include "stdafx.h" //6.13 — Void pointers @ http://www.learncpp.com/cpp-tutorial/613-void-pointers/
#include <iostream>
using std::cout;
using std::endl;

enum Type { INT, FLOAT, CSTRING };
 
void printValue(void* ptr, Type type) {
   switch (type) {
      case INT: std::cout << *static_cast<int*>(ptr) << '\n'; break; // cast to int pointer and dereference
      case FLOAT: std::cout << *static_cast<float*>(ptr) << '\n'; break; // cast to float pointer and dereference
      case CSTRING: std::cout << static_cast<char*>(ptr) << '\n'; // cast to char pointer and dereference
}	}

void voidPointers() {
	int nValue = 5;
	float fValue = 7.5;
	char szValue[] = "Mollie";
	printValue(&nValue, INT);
	printValue(&fValue, FLOAT);
	printValue(szValue, CSTRING);
	cout << '\n';
}

void myTest() {
	int i = 10;
	int* intPtr = &i;
	cout << *intPtr << endl;
	
	void* vPtr = &i;
	cout << *(static_cast<int*>(vPtr)) << endl << endl; //ERROR: cout << *vPtr << endl;
	//cout << *(reinterpret_cast<int*>(vPtr)) << endl << endl; //ERROR: cout << *vPtr << endl; //What is a handle in C++? @ http://stackoverflow.com/questions/1303123/what-is-a-handle-in-c
}

int main() {
	voidPointers();
	myTest();
	return 0;
}
