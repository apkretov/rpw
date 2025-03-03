#ifdef ON

#include <iostream>
using std::cout;

double x{}; //MINE

const char *mine1() { //MINE
	char c{'a'};
	return &c;
}

char *const mine2() { //MINE
	char c{'a'};
	return &c;
}

const char &mine3() { //MINE
	char c{'a'};
	return c;
}

char &mine4() { //MINE
	char c{'a'};
	return c;
}

const double f() { return 0.0; } //MINE

void The_decltype_Type_Specifier_1() {
	//TEST decltype(f()) sum = x; // 																																							sum has whatever type f returns

	//MINE
	//TEST! decltype(mine1()) a{};
	//TEST decltype(mine2()) b{}; 
	//TEST! decltype(mine3()) c{};
	//TEST!! decltype(mine4()) d{};
}

void The_decltype_Type_Specifier_2() {
	const int ci = 0, &cj = ci;
	//TEST decltype(ci) x = 0; // 																																								x has type const int
	//TEST decltype(cj) y = x; // 																																								y has type const int& and is bound to x
	//TEST decltype(cj) z; // 																																									error: z is a reference and must be initialized
	//TEST decltype(ci) a; //MINE
}

void decltype_and_References() {
	//																																															decltype of an expression can be a reference type
	int i = 42, *p = &i, &r = i;
	//TEST decltype(r + 0) b; //																																								ok: addition yields an int; b is an (uninitialized) int
	//TEST decltype(0) f; //MINE
	//TEST!!! decltype(*p) c; //																																								error: c is int& and must be initialized
	
	//																																															decltype of a parenthesized variable is always a reference
	//TEST!!! decltype((i)) d; //																																								error: d is int& and must be initialized
	//TEST decltype(i) e; //																																									ok: e is an (uninitialized) int
}

void mine5() { //MINE
	const int i{}, &r{i}, *p{&r};
	//TEST decltype(*p) a{};
	//TEST!! decltype(r) b;
	//TEST decltype(*p);
	//TEST int;
}

int main(int argc, char **argv) {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";
	
	decltype_and_References();

	return 0;
}
#endif

#undef EX_02_36
#ifdef EX_02_36

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int v = 3, b = 4;
	decltype(v) c = v;
	//TEST decltype((b)) d = a; 
	++c;
	//TEST ++d;

	return 0;
}
#endif

#undef EX_02_37
#ifdef EX_02_37

#include <iostream>
using std::cout;

int main(int argc, char **argv) {
	cout << "File: " << __FILE__ << "\tLine: " << __LINE__ << "\n\n";

	int v = 3, b = 4;
	decltype(v) c = v;
	//TEST decltype(a = b) d = a;

	return 0;
}
#endif