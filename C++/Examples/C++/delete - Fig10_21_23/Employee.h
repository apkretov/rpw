#ifndef EMPLOYEE_H // Fig. 10.21: Employee.h Employee class definition.
#define EMPLOYEE_H

class Employee {
public:
   Employee( const char * const, const char * const ); // constructor
   ~Employee(); // destructor
   const char *getFirstName() const; // return first name
   const char *getLastName() const; // return last name
	static int getCount(); // static member function // return number of objects instantiated
private:
   char *firstName;
   char *lastName;
   static int count; // static data // number of objects instantiated
};

#endif
