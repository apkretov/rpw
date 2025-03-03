#ifdef ON

#include <iostream>
using std::cout;

void The_auto_Type_Specifier() {
	auto i = 0, *p = &i; // ok: i is int and p is a pointer to int
	//TEST auto sz = 0, pi = 3.14; //																																											error: inconsistent types for sz and pi
}

void Compound_Types_const_and_auto() {
	int i = 0, &r = i;
	//TEST auto a = r; //																																														a is an int (r is an alias for i, which has type int)

	const int ci = i, &cr = ci;
	//TEST auto b = ci; //																																														b is an int (top-level const in ci is dropped)
	//TEST! auto c = cr; //																																														c is an int (cr is an alias for ci whose const is top-level)
	//TEST auto d = &i; // 																																														d is an int* (& of an int object is int*)
	//TEST!! auto e = &ci; // 																																													e is const int* (& of a const object is low-level const)

	//TEST const auto f = ci; //																																												deduced type of ci is int; f has type const int

	//TEST! auto &g = ci; //																																														g is a const int& that is bound to ci
	//TEST! auto &h = 42; //																																														error: we can’t bind a plain reference to a literal
	//TEST const auto &j = 42; //																																												ok: we can bind a const reference to a literal

	//TEST auto k = ci, &l = i; // 																																												k is int; l is int&
	//TEST! auto &m = ci, *p = &ci; // 																																											m is a const int&; p is a pointer to const int
	//TEST auto &n = i, *p2 = &ci; // 																																											error: type deduced from i is int; type deduced from &ci is const int
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	//The_auto_Type_Specifier();
	//Compound_Types_const_and_auto();

	return 0;
}
#endif

#undef EX_02_33
#ifdef EX_02_33

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int i = 0, &r = i;
	auto v = r; //																																											a is an int (r is an alias for i, which has type int)

	const int ci = i, &cr = ci;
	auto b = ci; // 																																										b is an int (top-level const in ci is dropped)
	auto c = cr; // 																																										c is an int (cr is an alias for ci whose const is top-level) 
	auto d = &i; // 																																										d is an int* (& of an int object is int*)
	auto e = &ci; // 																																										e is const int* (& of a const object is low-level const)

	const auto f = ci; // 																																									deduced type of ci is int; f has type const int

	auto &g = ci; // 																																										g is a const int& that is bound to ci

	//TEST a = 42; cout << i << '\t' << r << '\t' << a << "\n\n";
	b = 42;
	//TEST c = 42;
	//TEST d = 42; 
	//TEST e = 42;
	//TEST g = 42;

	return 0;
}
#endif

#undef EX_02_35
#ifdef EX_02_35

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	const int i = 42;
	auto j = i; 
	//TEST const auto &k = i; 
	//TEST auto *p = &i;
	//TEST const auto j2 = i, &k2 = i;

	return 0;
}
#endif