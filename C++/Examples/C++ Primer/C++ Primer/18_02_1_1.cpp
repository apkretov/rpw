#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Namespace Definitions
namespace cplusplus_primer {
	class Sales_data { /* ... */ };
	Sales_data operator+(const Sales_data &, const Sales_data &);
	class Query { /* ... */ };
	class Query_base { /* ... */ };
} // like blocks, namespaces do not end with a semicolon
#pragma endregion

#pragma region MINE
namespace AddisonWesley {
	class Query { /* ... */ };
}
#pragma endregion

void Each_Namespace_Is_a_Scope() {
	cplusplus_primer::Query q = cplusplus_primer::Query(/*ORIG "hello"*/);
	AddisonWesley::Query /*ORIG q*/q2 = AddisonWesley::Query(/*ORIG "hello"*/);
}

//#pragma region Defining Namespace Members
//
//#include "18_02_1_Sales_data.h" //ORIG #include "Sales_data.h"
//
//namespace cplusplus_primer { // reopen cplusplus_primer
//	istream & operator>>(istream &in, Sales_data &s) { // members defined inside the namespace may use unqualified names
//		/* ... */ 
//	} 
//}
//
//cplusplus_primer::Sales_data cplusplus_primer::operator+(const Sales_data &lhs, const Sales_data &rhs) { // namespace members defined outside the namespace must use qualified names
//	Sales_data ret(lhs);
//	// ...
//}
//#pragma endregion

int main() {
	print_file_line();

	Each_Namespace_Is_a_Scope();

	return 0;
}
#endif
