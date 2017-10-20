#include <iomanip> // Fig. 11.4: PhoneNumber.cpp // Overloaded stream insertion and stream extraction operators for class PhoneNumber.
using std::setw;
#include "PhoneNumber.h"

ostream &operator<<( ostream &output, const PhoneNumber &number ) { // overloaded stream insertion operator; cannot be a member function if we would like to invoke it with cout << somePhoneNumber;
   output << "(" << number.areaCode << ") " << number.exchange << "-" << number.line;
   return output; // enables cout << a << b << c;
}

istream &operator>>( istream &input, PhoneNumber &number ) { // overloaded stream extraction operator; cannot be a member function if we would like to invoke it with cin >> somePhoneNumber;
   input.ignore(); // skip (
   input >> setw( 3 ) >> number.areaCode; // input area code
   input.ignore( 2 ); // skip ) and space
   input >> setw( 3 ) >> number.exchange; // input exchange
   input.ignore(); // skip dash (-)
   input >> setw( 4 ) >> number.line; // input line
   return input; // enables cin >> a >> b >> c;
}
