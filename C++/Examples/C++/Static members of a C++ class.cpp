#include "stdafx.h" //Static members of a C++ class @ https://www.tutorialspoint.com/cplusplus/cpp_static_members.htm
#include <iostream>
using namespace std;

class Box {
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
   static int getCount() { return objectCount; }
private:
	double length, breadth, height;     // Length of a box // Breadth of a box // Height of a box
};

int Box::objectCount = 0; // Initialize static member of class Box

int main(void) {
   cout << "Inital Stage Count: " << Box::getCount() << endl; // Print total number of objects before creating object.
   Box Box1(3.3, 1.2, 1.5);    // Declare box1
   Box Box2(8.5, 6.0, 2.0);    // Declare box2
   cout << "Total objects: " << Box::objectCount << endl; // Print total number of objects.
	cout << "Final Stage Count: " << Box::getCount() << endl; // Print total number of objects after creating object.
   return 0;
}