#ifdef ON

#include <iostream>
using namespace std;
#ifndef Only_One_Class_Type_Conversion_Is_Allowed
#include "07_05_2.h"
#elif !Suppressing_Implicit_Conversions_Defined_by_Constructors
#include "07_05_4.h"
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Sales_data item; //MINE
#ifdef Implicit_Class_Type_Conversions
	string null_book = "9-999-99999-9";
	item.combine(null_book); // constructs a temporary Sales_data object // with units_sold and revenue equal to 0 and bookNo equal to null_book
#elif !Only_One_Class_Type_Conversion_Is_Allowed
	item.combine(string("9-999-99999-9")); //TEST //																																		ok: explicit conversion to string, implicit conversion to Sales_data
	item.combine(Sales_data("9-999-99999-9")); //TEST //																																	ok: implicit conversion to string, explicit conversion to Sales_data

#elif Suppressing_Implicit_Conversions_Defined_by_Constructors
	item.combine(null_book); //TEST //																																						error: string constructor is explicit
	item.combine(cin); //TEST //																																							error: istream constructor is explicit

#elif explicit_Constructors_Can_Be_Used_Only_for_Direct_Initialization
	Sales_data item1(null_book); //TEST //																																					ok: direct initialization
	Sales_data item2 = null_book; //TEST! //																																				error: cannot use the copy form of initialization with an explicit constructor

#elif Explicitly_Using_Constructors_for_Conversions
	item.combine(Sales_data(null_book)); //TEST  																																				//ok: the argument is an explicitly constructed Sales_data object
	item.combine(static_cast<Sales_data>(cin)); //TEST  																																		// ok: static_cast can use an explicit constructor
#endif

	return 0;
}
#endif

#ifdef EX_07_48

#include <iostream>
#include <string>
using namespace std;

#ifdef IMPLICIT
#define Delegating_Constructors
#include "07_05_2.h"
#elif !EXPLICIT
#include "07_05_4.h"
#endif

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	string null_isbn("9-999-99999-9");
	Sales_data item1(null_isbn);
	Sales_data item2("9-999-99999-9"); //TEST!

	return 0;
}

#endif

#ifdef EX_07_49

#include <iostream>
using namespace std;
#include "07_05_4.h"

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	Sales_data i;
	string s;
	//ERR i.combine(s);

	return 0;
}
#endif