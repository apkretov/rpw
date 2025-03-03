#ifdef ON

#include <iostream>
#include "../../stdafx.h"
#include "16_01_1.h"
using namespace std;

#pragma region Specifying an Explicit Template Argument
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3); //TEST! //																																	T1 cannot be deduced: it doesn’t appear in the function parameter list

constexpr int i{}; //MINE
constexpr long lng{}; //MINE

void Specifying_an_Explicit_Template_Argument_1() {
	auto val3 = sum<long long>(i, lng); //TEST! //																											long long sum(int, long) // T1 is explicitly specified; T2 and T3 are inferred from the argument types
}

template <typename T1, typename T2, typename T3>
T3 alternative_sum(T2, T1); // poor design: users must explicitly specify all three template parameters

void Specifying_an_Explicit_Template_Argument_2() {
	//TEST! auto val3 = alternative_sum<long long>(i, lng); //																								error: can’t infer initial template parameters
	auto val2 = alternative_sum<long long, int, long>(i, lng); //TEST! //																					ok: all three parameters are explicitly specified
}
#pragma endregion

void Normal_Conversions_Apply_for_Explicitly_Specified_Arguments() {
	long lng;
	//ERR compare(lng, 1024); // error: template parameters don’t match
	compare<long>(lng, 1024); //TEST! //																													ok: instantiates compare(long, long)
	compare<int>(lng, 1024); //TEST! //																														ok: instantiates compare(int, int)
}

int main() {
	print_file_line();
}
#endif

#ifdef EX_16_37

#include <iostream>
#include "../../stdafx.h"
using namespace std;

int main() {
	print_file_line();

	auto n1 = max(1, 2);
	auto n2 = max<int>(1, 2.2); //TEST!
	auto n3 = max<double>(1, 2.2); //TEST!

	cout << "max(1, 2) = " << n1 << '\n';
	cout << "max<int>(1, 2.2) = " << n2 << '\n';
	cout << "max<double>(1, 2.2) = " << n3 << '\n';
}
#endif

#ifdef EX_16_39

#include <iostream>
#include "../../stdafx.h"
#include "16_01_1.h"
using namespace std;

int main() {
	print_file_line();

	cout << R"(compare("bye", "dad") = )" << compare("bye", "dad") << '\n'; 
	cout << R"(compare<string>("bye", "dad") = )" << compare<string>("bye", "dad") << '\n'; //TEST!
}
#endif