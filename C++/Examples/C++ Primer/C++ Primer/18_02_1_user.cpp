#ifdef ON

#include <iostream>
#include "../../stdafx.h"
using namespace std;

#pragma region Defining the Primer Namespace
//ORIG #include "Sales_data.h" // ---- user.cc ---- // names in the Sales_data.h header are in the cplusplus_primer namespace
#include "18_02_1_Sales_data.h"
int main() {
	print_file_line();

	using cplusplus_primer::Sales_data;
	Sales_data trans1, trans2;
	// ...
	return 0;
}
#pragma endregion
#endif
