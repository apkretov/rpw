#ifndef PHONENUMBER_H // Fig. 11.3: PhoneNumber.h // PhoneNumber class definition
#define PHONENUMBER_H
#include <iostream>
using std::ostream;
using std::istream;
#include <string>
using std::string;

class PhoneNumber {
   friend ostream &operator<<( ostream &, const PhoneNumber & );
   friend istream &operator>>( istream &, PhoneNumber & );
private:
   string areaCode; // 3-digit area code 
   string exchange; // 3-digit exchange 
   string line; // 4-digit line 
};
#endif