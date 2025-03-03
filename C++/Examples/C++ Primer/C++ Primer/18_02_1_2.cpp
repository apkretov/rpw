#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "16_05_1.h"
using namespace std;

#pragma region Defining Namespace Members

#include "18_02_1_Sales_data.h" //ORIG #include "Sales_data.h"

namespace cplusplus_primer { // reopen cplusplus_primer
	istream &operator>>(istream &in, Sales_data &s) { // members defined inside the namespace may use unqualified names
		/* ... */ 
		return in; //MINE
	} 
}

cplusplus_primer::Sales_data cplusplus_primer::operator+(const Sales_data &lhs, const Sales_data &rhs) { // namespace members defined outside the namespace must use qualified names
	Sales_data ret(lhs);
	// ...
	return ret; //MINE
}
#pragma endregion

#pragma region Template Specializations
namespace std { // we must declare the specialization as a member of std
	template <> 
	struct hash<Sales_data>;
}

template <>				  // having added the declaration for the specialization to std 
struct hash<Sales_data> { // we can define the specialization outside the std namespace
	size_t operator()(const Sales_data &s) const {
		return hash<string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
	// other members as before
};
#pragma endregion

#pragma region Nested Namespaces
namespace cplusplus_primer {
	namespace QueryLib { // first nested namespace: defines the Query portion of the library
		class Query { /* ... */ };
		Query operator&(const Query &, const Query &);
		// ...
	}
	
	namespace Bookstore { // second nested namespace: defines the Sales_data portion of the library
		class Quote { /* ... */ };
		class Disc_quote : public Quote { /* ... */ };
		// ...
	}
}

cplusplus_primer::QueryLib::Query q; //MINE
#pragma endregion

#pragma region Inline Namespaces
inline namespace FifthEd { //TEST!
	// namespace for the code from the Primer Fifth Edition
}

namespace FifthEd { //TEST! //																																implicitly inline
	class Query_base { /* ... */ };
	// other Query-related declarations
}

namespace FourthEd {
	class Item_base { /* ... */ };
	class Query_base { /* ... */ };
	// other code from the Fourth Edition
}

namespace cplusplus_primer {
//TEST! #include "FifthEd.h"
//OFF #include "FourthEd.h"
}
#pragma endregion

#pragma region Unnamed Namespaces
int i; // global declaration for i
namespace { //TEST!
	int i;
}
void Unnamed_Namespaces_1() {
	//TEST! i = 10; //																																		ambiguous: defined globally and in an unnested, unnamed namespace
}

namespace local {
	namespace { //TEST
		int i;
	}
}

void Unnamed_Namespaces_2() {
	local::i = 42; //TEST
}
#pragma endregion

int main() {
	print_file_line();
	return 0;
}
#endif

#ifdef EX_18_14

#include <iostream>
#include "../../stdafx.h"
using namespace std;

namespace mathLib {
	namespace MatrixLib {
		class matrix { /* ... */ };
		matrix operator*(const matrix &, const matrix &);
		// ...
	}
}

int main() {
	print_file_line();
	
	mathLib::MatrixLib::matrix mathLib::MatrixLib::operator*(const mathLib::MatrixLib::matrix &, const mathLib::MatrixLib::matrix &);

	using mathLib::MatrixLib::matrix;
	matrix mathLib::MatrixLib::operator*(const matrix &, const matrix &);

	return 0;
}
#endif