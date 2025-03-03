#pragma once

#pragma region Defining the Primer Namespace

#include <string> // ---- Sales_data.h ---- // #includes should appear before opening the namespace

namespace cplusplus_primer {
	class Sales_data { /* ... */ };
	Sales_data operator+(const Sales_data &, const Sales_data &);
	// declarations for the remaining functions in the Sales_data interface
	Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs); //MINE
}
#pragma endregion
