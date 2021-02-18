#include "stdafx.h"
#include <iostream>
using std::cout;
using std::endl;

class test {
public:
	static int count;
	test() { count++; }
	~test() { count--; }
};
int test::count = 0;

void test_() {
	cout << "test::count = " << test::count << endl;
	test objTest;
	cout << "test::count = " << test::count << endl;
	test* ptrTest;
	ptrTest = new test();
	cout << "test::count = " << test::count << endl;
	delete ptrTest;
	ptrTest = nullptr;
	cout << "test::count = " << test::count << endl;
	cout << endl;
}

class Box { //Static members of a C++ class @ https://www.tutorialspoint.com/cplusplus/cpp_static_members.htm
   double length;     // Length of a box
   double breadth;    // Breadth of a box
   double height;     // Height of a box
public:
   static int objectCount;
	Box(double l = 2.0, double b = 2.0, double h = 2.0) { // Constructor definition
      cout <<"Constructor called." << endl;
      length = l;
      breadth = b;
      height = h;
      objectCount++; // Increase every time object is created
   }
   double Volume() { return length * breadth * height; }
};
int Box::objectCount = 0; // Initialize static member of class Box

void Box_() {
   Box Box1(3.3, 1.2, 1.5);    // Declare box1
   Box Box2(8.5, 6.0, 2.0);    // Declare box2
   cout << "Total objects: " << Box::objectCount << endl << endl; // Print total number of objects.
}

int main() {
	test_();
	Box_();
	return 0;
}
