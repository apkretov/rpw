#include "stdafx.h"
#include <iostream> // Fig. 10.23: fig10_23.cpp. static data member tracking the number of objects of a class.
using std::cout;
using std::endl;
#include "Employee.h" // Employee class definition
#include <vector> //TEST

Employee *g_e1Ptr; //TEST.

void fig10_23() { // use class name and binary scope resolution operator to access static number function getCount
	cout << "Number of employees before instantiation of any objects is " << Employee::getCount() << endl; // use class name
	Employee *e1Ptr = new Employee("Susan", "Baker"); // use new to dynamically create two new Employees operator new also calls the object's constructor
	Employee *e2Ptr = new Employee("Robert", "Jones");
	cout << "Number of employees after objects are instantiated is " << e1Ptr->getCount(); // call getCount on first Employee object
	cout << "\n\nEmployee 1: " << e1Ptr->getFirstName() << " " << e1Ptr->getLastName() << "\nEmployee 2: " << e2Ptr->getFirstName() << " " << e2Ptr->getLastName() << "\n\n";
	delete e1Ptr; // deallocate memory
	e1Ptr = 0; // disconnect pointer from free-store space //TEST: THIS ISN'T NECESSARY, EVEN IF THE POINTER IS IN THE GLOBAL SCOPE. A GLOBAL POINTER CAN BE REUSED TO POINT TO ANOTHER OBJECT OF THE CLASS.
	delete e2Ptr; // deallocate memory
	e2Ptr = 0; // disconnect pointer from free-store space //TEST: THIS ISN'T NECESSARY, EVEN IF THE POINTER IS IN THE GLOBAL SCOPE. A GLOBAL POINTER CAN BE REUSED TO POINT TO ANOTHER OBJECT OF THE CLASS.
	cout << "Number of employees after objects are deleted is " << Employee::getCount() << endl; // no objects exist, so call static member function getCount again using the class name and the binary scope resolution operator
}

void memoryLeak() { // use class name and binary scope resolution operator to access static number function getCount
	cout << "Memory leak test started.\n";
	for (size_t i = 0; i < 20000000; i++) {
		g_e1Ptr = new Employee("Susan", "Baker"); //TEST
		//TEST delete e1Ptr; // deallocate memory
		//TEST e1Ptr = 0; // disconnect pointer from free-store space //THIS ISN'T NECESSARY, EVEN IF THE POINTER IS IN THE GLOBAL SCOPE. A GLOBAL POINTER CAN BE REUSED TO POINT TO ANOTHER OBJECT OF THE CLASS.
	}
	cout << "Memory leak test finished.\n";
}

void vectoreClear() { // use class name and binary scope resolution operator to access static number function getCount
	cout << "vector clearing test started.\n";
	std::vector <Employee*> objEmployees;
	objEmployees.push_back(new Employee("Susan", "Baker"));
	//TEST delete objEmployees[0]; // deallocate memory
	objEmployees.clear(); //TEST: IT DOESN'T DELETE THE OBJECTS.
	cout << "vector clearing test finished.\n";
}

int main() { 
	//fig10_23();
	//memoryLeak();
	vectoreClear();
	std::cin.get();
	std::cin.ignore();
	return 0;
}
