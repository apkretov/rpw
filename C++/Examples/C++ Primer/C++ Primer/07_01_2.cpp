#include <iostream>
using namespace std;
#ifdef Defining_the_Revised_Sales_data_Class
#include "07_01_2.h"
#elif Defining_the_Sales_data_Constructors
#include "07_01_4.h"
#elif Access_Control_and_Encapsulation
#include "07_02.h"
#elif Friends
#include "07_02_1.h"
#elif Default_Arguments_and_Constructors
#include "07_05_1.h"
#elif Delegating_Constructors
#include "07_05_2.h"
#elif !Suppressing_Implicit_Conversions_Defined_by_Constructors
#include "07_05_4.h"
#endif

#ifndef Defining_a_Member_Function_outside_the_Class 
#ifdef Access_Control_and_Encapsulation
double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
#endif

#ifndef Defining_a_Function_to_Return_This_Object
Sales_data &Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold; // add the members of rhs into
	revenue += rhs.revenue; // the members of ‘‘this’’ object
	return *this; // return the object on which the function was called
}
#endif
#endif

#ifdef ON
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//MINE
	Sales_data total, trans;
	total.units_sold = 10;
	total.revenue = 100;
	trans.units_sold = 5;
	trans.revenue = 50;
	total.combine(trans);
	cout << total.units_sold << '\n';
	cout << total.revenue << '\n';

	return 0;
}
#endif
