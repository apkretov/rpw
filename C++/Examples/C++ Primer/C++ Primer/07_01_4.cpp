#include <iostream>
using namespace std;
#ifdef Defining_the_Sales_data_Constructors
#include "07_01_4.h"
#elif Access_Control_and_Encapsulation
#include "07_02.h"
#elif Friends
#include "07_02_1.h"
#elif Default_Arguments_and_Constructors
#include "07_05_1.h"
#elif !Suppressing_Implicit_Conversions_Defined_by_Constructors
#include "07_05_4.h"
#endif

#ifndef Defining_a_Constructor_outside_the_Class_Body
//TEST!!! explicit Sales_data::Sales_data(istream &is) { //																																				error: explicit allowed only on a constructor declaration in a class header
Sales_data::Sales_data(istream &is) {
	read(is, *this);
}
#endif

#ifdef ON
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE

#ifdef _1
	Sales_data s1;
	print(cout, s1);
	cout << '\n';

	Sales_data s2("aaa");
	print(cout, s2);
	cout << '\n';

	Sales_data s3("bbb", 10, 100);
	print(cout, s3);
	cout << '\n';
#endif

#ifndef _2
	Sales_data s4(cin);
	print(cout, s4);
	cout << '\n';
#endif

	return 0;
}
#endif