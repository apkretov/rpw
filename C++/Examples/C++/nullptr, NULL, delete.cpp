#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

template <typename T> bool CheckPointer(T ptr) { return ptr == nullptr ? POINTER_INVALID : POINTER_DYNAMIC; }

class foo {
public:
	int x;
	void operator()() { foo(); };
};

int main() {
	foo* ptrFoo1 = new foo();
	foo* ptrFoo2 = new foo;
	ptrFoo1->x = 10;
	ptrFoo2->x = 20;
	cout << "ptrFoo1 == nullptr: " << (ptrFoo1 == nullptr) << endl;
	cout << "ptrFoo1->x: " << ptrFoo1->x << endl;
	cout << "ptrFoo2->x: " << ptrFoo2->x << endl;
	delete ptrFoo1;
	cout << "ptrFoo1 == nullptr: " << (ptrFoo1 == nullptr) << endl; //"test to see if object exists with new / delete usage" @ https://bytes.com/topic/c/answers/141115-test-see-if-object-exists-new-delete-usage 
	cout << "ptrFoo1 == NULL: " << (ptrFoo1 == NULL) << endl;
	//ERROR AFTER DELETING ptrFoo1: cout << "ptrFoo1->x: " << ptrFoo1->x << endl;
	cout << "ptrFoo1: " << ptrFoo1 << endl;
	ptrFoo1 = nullptr; //"disconnect pointer from free-store space" C++ Fundamentals By Paul J. Lesson09\Fig10_21_23\fig10_23.cpp //"test to see if object exists with new / delete usage" @ https://bytes.com/topic/c/answers/141115-test-see-if-object-exists-new-delete-usage 
	cout << "ptrFoo1 == nullptr: " << (ptrFoo1 == nullptr) << endl;
	cout << "ptrFoo1 == NULL: " << (ptrFoo1 == NULL) << endl;
	return 0;
}
