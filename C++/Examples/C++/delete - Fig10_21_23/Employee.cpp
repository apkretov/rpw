#include "stdafx.h"
#pragma warning(disable: 4996) //To use the localtime() function instead of a safe localtime_s() suggested. //TO DO: Use the safe localtime_s() function suggested.
#include <iostream> // Fig. 10.22: Employee.cpp // Employee class member-function definitions.
using std::cout;
using std::endl;
#include <cstring> // strlen and strcpy prototypes
using std::strlen;
using std::strcpy;
#include "Employee.h" // Employee class definition 
int Employee::count = 0; // define and initialize static data member at file scope // cannot include keyword static
// define static member function that returns number of 
// Employee objects instantiated (declared static in Employee.h)
int Employee::getCount() 
{ 
   return count; 
} // end static function getCount

// constructor dynamically allocates space for first and last name and 
// uses strcpy to copy first and last names into the object
Employee::Employee( const char * const first, const char * const last )
{
   firstName = new char[ strlen( first ) + 1 ]; // create space
   strcpy( firstName, first ); // copy first into object

   lastName = new char[ strlen( last ) + 1 ]; // create space
   strcpy( lastName, last ); // copy first into object

   count++; // increment static count of employees

   cout << "Employee constructor for " << firstName << ' ' << lastName << " called." << endl;
}

// destructor deallocates dynamically allocated memory
Employee::~Employee()
{
	cout << "~Employee() called for " << firstName << ' ' << lastName << endl;

   delete [] firstName; // release memory
   delete [] lastName; // release memory

   count--; // decrement static count of employees
}

// return first name of employee
const char *Employee::getFirstName() const
{
   // const before return type prevents client from modifying
   // private data; client should copy returned string before
   // destructor deletes storage to prevent undefined pointer
   return firstName;
}

// return last name of employee
const char *Employee::getLastName() const
{
   // const before return type prevents client from modifying
   // private data; client should copy returned string before
   // destructor deletes storage to prevent undefined pointer
   return lastName;
}
